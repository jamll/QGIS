/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/gui/qgsattributetypeloaddialog.h                                 *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/





class QgsAttributeTypeLoadDialog: QDialog
{

%TypeHeaderCode
#include "qgsattributetypeloaddialog.h"
%End
  public:
    QgsAttributeTypeLoadDialog( QgsVectorLayer *vl );

    virtual void accept();

%Docstring
Overloaded accept method which will write the feature field
values, then delegate to QDialog.accept()
%End

    void setVectorLayer( QgsVectorLayer *layer );
%Docstring
Sets predefined vector layer for selection of data

:param layer: Vector layer which is to be set as predefined one
%End

    QMap<QString, QVariant> &valueMap();
%Docstring
Getter to value map which is currently active

:return: value map of vlues selected from layer
%End

    bool insertNull();
%Docstring
Returns true if the "Add NULL value" checkbox has been checked.

:return: true if the "Add NULL value" checkbox has been checked.
%End

};

/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/gui/qgsattributetypeloaddialog.h                                 *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/
