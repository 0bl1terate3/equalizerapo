/*
	This file is part of EqualizerAPO, a system-wide equalizer.
	Copyright (C) 2016  Jonas Thedering

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#include "CustomStyle.h"
#include "Editor/helpers/GUIHelper.h"
#include <QPalette> // Required for QPalette
#include <QApplication> // Required for qApp
#include <QColor> // Required for QColor

CustomStyle::CustomStyle(QStyle* style)
	: QProxyStyle(style)
{
}

int CustomStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option, const QWidget* widget) const
{
	switch (metric)
	{
	case PM_ToolBarIconSize:
	case PM_TabBarIconSize:
		return GUIHelper::scale(16);
	case PM_DockWidgetTitleBarButtonMargin:
		return GUIHelper::scale(baseStyle()->pixelMetric(metric, option, widget));
	default:
		return baseStyle()->pixelMetric(metric, option, widget);
	}
}

QIcon CustomStyle::standardIcon(StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
	// GUIHelper::isDarkMode() will reflect the active theme (Light vs any Dark variant including System Dark)
	if(GUIHelper::isDarkMode())
	{
		switch (standardIcon)
		{
		case QStyle::SP_ToolBarHorizontalExtensionButton :
			return QIcon(":/icons/dark-mode/toolbar-ext-h.svg");

		case QStyle::SP_ToolBarVerticalExtensionButton :
			return QIcon(":/icons/dark-mode/toolbar-ext-v.svg");

		default:
			break;
		}
	}

	return QProxyStyle::standardIcon(standardIcon, option, widget);
}

QPalette CustomStyle::standardPalette() const
{
    QPalette palette = QProxyStyle::standardPalette(); // Start with the base style's palette

    GUIHelper::Theme currentTheme = GUIHelper::currentTheme;

    if (currentTheme == GUIHelper::Light) {
        // Explicit Light theme
        palette.setColor(QPalette::Window, Qt::white);
        palette.setColor(QPalette::WindowText, Qt::black);
        palette.setColor(QPalette::Base, QColor(245, 245, 245)); // Slightly off-white for base
        palette.setColor(QPalette::AlternateBase, QColor(230, 230, 230)); // Slightly darker for alternate
        palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220)); // Standard light tooltip
        palette.setColor(QPalette::ToolTipText, Qt::black);
        palette.setColor(QPalette::Text, Qt::black);
        palette.setColor(QPalette::Button, QColor(240, 240, 240));
        palette.setColor(QPalette::ButtonText, Qt::black);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(0, 0, 255));
        palette.setColor(QPalette::Highlight, QColor(0, 120, 215)); // Standard Windows/Qt highlight
        palette.setColor(QPalette::HighlightedText, Qt::white);
    } else if (currentTheme == GUIHelper::Dark) {
        // Generic Dark theme
        palette.setColor(QPalette::Window, QColor(53, 53, 53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(25, 25, 25));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45)); // Slightly lighter than base
        palette.setColor(QPalette::ToolTipBase, QColor(53, 53, 53)); // Dark tooltip base
        palette.setColor(QPalette::ToolTipText, Qt::white);       // Light text on dark tooltip
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(53, 53, 53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, QColor(255, 85, 85)); // Brighter red
        palette.setColor(QPalette::Link, QColor(100, 150, 255)); // Lighter blue for links
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::white); // White text on highlight
    } else if (currentTheme == GUIHelper::SolarizedDark) {
        palette.setColor(QPalette::Window, QColor(0x00, 0x2b, 0x36)); // Base03
        palette.setColor(QPalette::WindowText, QColor(0x83, 0x94, 0x96)); // Base0
        palette.setColor(QPalette::Base, QColor(0x07, 0x36, 0x42)); // Base02
        palette.setColor(QPalette::AlternateBase, QColor(0x00, 0x2b, 0x36)); // Base03
        palette.setColor(QPalette::ToolTipBase, QColor(0x07, 0x36, 0x42)); // Base02
        palette.setColor(QPalette::ToolTipText, QColor(0x93, 0xa1, 0xa1)); // Base1
        palette.setColor(QPalette::Text, QColor(0x93, 0xa1, 0xa1)); // Base1
        palette.setColor(QPalette::Button, QColor(0x07, 0x36, 0x42)); // Base02
        palette.setColor(QPalette::ButtonText, QColor(0x93, 0xa1, 0xa1)); // Base1
        palette.setColor(QPalette::BrightText, QColor(0xcb, 0x4b, 0x16)); // Orange
        palette.setColor(QPalette::Link, QColor(0x26, 0x8b, 0xd2)); // Blue
        palette.setColor(QPalette::Highlight, QColor(0x26, 0x8b, 0xd2)); // Blue
        palette.setColor(QPalette::HighlightedText, QColor(0x00, 0x2b, 0x36)); // Base03
    } else if (currentTheme == GUIHelper::Dracula) {
        palette.setColor(QPalette::Window, QColor(0x28, 0x2a, 0x36)); // Background
        palette.setColor(QPalette::WindowText, QColor(0xf8, 0xf8, 0xf2)); // Foreground
        palette.setColor(QPalette::Base, QColor(0x28, 0x2a, 0x36)); // Background
        palette.setColor(QPalette::AlternateBase, QColor(0x44, 0x47, 0x5a)); // Current Line
        palette.setColor(QPalette::ToolTipBase, QColor(0x44, 0x47, 0x5a)); // Current Line for tooltip base
        palette.setColor(QPalette::ToolTipText, QColor(0xf8, 0xf8, 0xf2)); // Foreground for tooltip text
        palette.setColor(QPalette::Text, QColor(0xf8, 0xf8, 0xf2)); // Foreground
        palette.setColor(QPalette::Button, QColor(0x44, 0x47, 0x5a)); // Current Line
        palette.setColor(QPalette::ButtonText, QColor(0xf8, 0xf8, 0xf2)); // Foreground
        palette.setColor(QPalette::BrightText, QColor(0xff, 0x55, 0x55)); // Red
        palette.setColor(QPalette::Link, QColor(0xbd, 0x93, 0xf9)); // Purple
        palette.setColor(QPalette::Highlight, QColor(0x44, 0x47, 0x5a)); // Current Line
        palette.setColor(QPalette::HighlightedText, QColor(0xf1, 0xfa, 0x8c)); // Yellow for highlighted text for better contrast
    } else if (currentTheme == GUIHelper::Nord) {
        palette.setColor(QPalette::Window, QColor(0x2E, 0x34, 0x40)); // nord0
        palette.setColor(QPalette::WindowText, QColor(0xD8, 0xDE, 0xE9)); // nord4
        palette.setColor(QPalette::Base, QColor(0x3B, 0x42, 0x52)); // nord1
        palette.setColor(QPalette::AlternateBase, QColor(0x43, 0x4C, 0x5E)); // nord2
        palette.setColor(QPalette::ToolTipBase, QColor(0x4C, 0x56, 0x6A)); // nord3
        palette.setColor(QPalette::ToolTipText, QColor(0xE5, 0xE9, 0xF0)); // nord5
        palette.setColor(QPalette::Text, QColor(0xD8, 0xDE, 0xE9)); // nord4
        palette.setColor(QPalette::Button, QColor(0x43, 0x4C, 0x5E)); // nord2 for buttons
        palette.setColor(QPalette::ButtonText, QColor(0xECE, 0xFF, 0xF4)); // nord6
        palette.setColor(QPalette::BrightText, QColor(0xBF, 0x61, 0x6A)); // nord11 (Aurora Red)
        palette.setColor(QPalette::Link, QColor(0x88, 0xC0, 0xD0)); // nord8 (Frost Lighter Blue)
        palette.setColor(QPalette::Highlight, QColor(0x5E, 0x81, 0xAC)); // nord10 (Frost Darker Blue)
        palette.setColor(QPalette::HighlightedText, QColor(0xECE, 0xFF, 0xF4)); // nord6
    }
    // Handle System theme explicitly based on underlying OS dark mode detection
    else if (currentTheme == GUIHelper::System) {
        if (GUIHelper::isDarkMode()) { // Check if system is in dark mode
            // Apply Generic Dark theme colors or system-specific dark colors
            palette.setColor(QPalette::Window, QColor(53, 53, 53));
            palette.setColor(QPalette::WindowText, Qt::white);
            palette.setColor(QPalette::Base, QColor(25, 25, 25));
            palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
            palette.setColor(QPalette::ToolTipBase, QColor(53, 53, 53));
            palette.setColor(QPalette::ToolTipText, Qt::white);
            palette.setColor(QPalette::Text, Qt::white);
            palette.setColor(QPalette::Button, QColor(53, 53, 53));
            palette.setColor(QPalette::ButtonText, Qt::white);
            palette.setColor(QPalette::BrightText, QColor(255, 85, 85));
            palette.setColor(QPalette::Link, QColor(100, 150, 255));
            palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            palette.setColor(QPalette::HighlightedText, Qt::white);
        } else {
            // System is in light mode, apply explicit Light theme or rely on QProxyStyle::standardPalette()
             palette.setColor(QPalette::Window, Qt::white);
            palette.setColor(QPalette::WindowText, Qt::black);
            palette.setColor(QPalette::Base, QColor(245, 245, 245));
            palette.setColor(QPalette::AlternateBase, QColor(230, 230, 230));
            palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
            palette.setColor(QPalette::ToolTipText, Qt::black);
            palette.setColor(QPalette::Text, Qt::black);
            palette.setColor(QPalette::Button, QColor(240, 240, 240));
            palette.setColor(QPalette::ButtonText, Qt::black);
            palette.setColor(QPalette::BrightText, Qt::red);
            palette.setColor(QPalette::Link, QColor(0, 0, 255));
            palette.setColor(QPalette::Highlight, QColor(0, 120, 215));
            palette.setColor(QPalette::HighlightedText, Qt::white);
        }
    }

    return palette;
}
