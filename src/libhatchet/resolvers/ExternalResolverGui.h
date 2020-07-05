/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Hatchet is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hatchet is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hatchet. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EXTERNALRESOLVERGUI_H
#define EXTERNALRESOLVERGUI_H

#include "ExternalResolver.h"
#include "DllMacro.h"

#include <QPixmap>

class QWidget;
class AccountConfigWidget;

namespace Hatchet
{

/**
 * Generic resolver object, used to manage a resolver that Hatchet knows about
 *
 * You *must* start() a resolver after creating an ExternalResolver in order to use it,
 * otherwise it will not do anything.
 */
class DLLEXPORT ExternalResolverGui : public ExternalResolver
{
Q_OBJECT

public:
    ExternalResolverGui( const QString& filePath );
    virtual AccountConfigWidget* configUI() const = 0;

protected:
    AccountConfigWidget* widgetFromData( QByteArray& data, QWidget* parent = 0 );
    QVariant configMsgFromWidget( QWidget* w );
    QByteArray fixDataImagePaths( const QByteArray& data, bool compressed, const QVariantMap& images );

private:
    void addChildProperties( QObject* widget, QVariantMap& m );
    void setupClickHandlerOnUrlButtons( QObject* widget );
};

}; //ns

#endif // RESOLVER_H
