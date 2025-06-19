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

// Add this method to CustomStyle
QPalette CustomStyle::standardPalette() const
{
    QPalette palette = QProxyStyle::standardPalette();
    if (GUIHelper::isDarkMode()) {
        // Dark theme colors
        palette.setColor(QPalette::Window, QColor(53, 53, 53));
        palette.setColor(QPalette::WindowText, Qt::white);
        // You can add more color role changes here for a complete dark theme
        // For example:
        // palette.setColor(QPalette::Base, QColor(25, 25, 25));
        // palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        // palette.setColor(QPalette::ToolTipBase, Qt::white);
        // palette.setColor(QPalette::ToolTipText, Qt::white);
        // palette.setColor(QPalette::Text, Qt::white);
        // palette.setColor(QPalette::Button, QColor(53, 53, 53));
        // palette.setColor(QPalette::ButtonText, Qt::white);
        // palette.setColor(QPalette::BrightText, Qt::red);
        // palette.setColor(QPalette::Link, QColor(42, 130, 218));
        // palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        // palette.setColor(QPalette::HighlightedText, Qt::black);
    } else {
        // Light theme colors (or default)
        palette.setColor(QPalette::Window, Qt::white);
        palette.setColor(QPalette::WindowText, Qt::black);
        // Define other colors for light theme if necessary
    }
    return palette;
}
