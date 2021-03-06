/***************************************************************************
                         qgslayoutpolygonwidget.cpp
    begin                : March 2016
    copyright            : (C) 2016 Paul Blottiere, Oslandia
    email                : paul dot blottiere at oslandia dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgslayoutpolygonwidget.h"
#include "qgssymbolselectordialog.h"
#include "qgsstyle.h"
#include "qgslayout.h"
#include "qgssymbollayerutils.h"
#include "qgslayoutitemregistry.h"
#include "qgslayoutundostack.h"

QgsLayoutPolygonWidget::QgsLayoutPolygonWidget( QgsLayoutItemPolygon *polygon )
  : QgsLayoutItemBaseWidget( nullptr, polygon )
  , mPolygon( polygon )
{
  setupUi( this );
  setPanelTitle( tr( "Polygon properties" ) );

  //add widget for general composer item properties
  mItemPropertiesWidget = new QgsLayoutItemPropertiesWidget( this, polygon );
  //shapes don't use background or frame, since the symbol style is set through a QgsSymbolSelectorWidget
  mItemPropertiesWidget->showBackgroundGroup( false );
  mItemPropertiesWidget->showFrameGroup( false );
  mainLayout->addWidget( mItemPropertiesWidget );

  mPolygonStyleButton->setSymbolType( QgsSymbol::Fill );
  connect( mPolygonStyleButton, &QgsSymbolButton::changed, this, &QgsLayoutPolygonWidget::symbolChanged );

  if ( mPolygon )
  {
    connect( mPolygon, &QgsLayoutObject::changed, this, &QgsLayoutPolygonWidget::setGuiElementValues );
    mPolygonStyleButton->registerExpressionContextGenerator( mPolygon );
  }

  setGuiElementValues();
#if 0 //TODO
  mShapeStyleButton->setLayer( atlasCoverageLayer() );
#endif
}

bool QgsLayoutPolygonWidget::setNewItem( QgsLayoutItem *item )
{
  if ( item->type() != QgsLayoutItemRegistry::LayoutPolygon )
    return false;

  if ( mPolygon )
  {
    disconnect( mPolygon, &QgsLayoutObject::changed, this, &QgsLayoutPolygonWidget::setGuiElementValues );
  }

  mPolygon = qobject_cast< QgsLayoutItemPolygon * >( item );
  mItemPropertiesWidget->setItem( mPolygon );

  if ( mPolygon )
  {
    connect( mPolygon, &QgsLayoutObject::changed, this, &QgsLayoutPolygonWidget::setGuiElementValues );
    mPolygonStyleButton->registerExpressionContextGenerator( mPolygon );
  }
  setGuiElementValues();

  return true;
}

void QgsLayoutPolygonWidget::setGuiElementValues()
{
  if ( !mPolygon )
  {
    return;
  }

  whileBlocking( mPolygonStyleButton )->setSymbol( mPolygon->symbol()->clone() );
}

void QgsLayoutPolygonWidget::symbolChanged()
{
  if ( !mPolygon )
    return;

  mPolygon->layout()->undoStack()->beginCommand( mPolygon, tr( "Change Shape Style" ), QgsLayoutItem::UndoShapeStyle );
  mPolygon->setSymbol( mPolygonStyleButton->clonedSymbol<QgsFillSymbol>() );
  mPolygon->layout()->undoStack()->endCommand();
}
