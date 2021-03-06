/* === This file is part of Hatchet Player - <http://hatchet-player.org> ===
 *
 *   Copyright 2011, Teo Mrnjavac <teo@kde.org>
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

#ifndef MP4TAG_H
#define MP4TAG_H

#include "tag.h"
#include <taglib/mp4tag.h>

namespace Hatchet
{

class DLLEXPORT MP4Tag : public Tag
{
public:
    MP4Tag( TagLib::Tag *, TagLib::MP4::Tag * );

    virtual QString albumArtist() const { return m_albumArtist; }
    virtual QString composer() const { return m_composer; }
    virtual unsigned int discNumber() const { return m_discNumber; }

private:
    TagLib::MP4::Tag *m_mp4Tag;
};

}
#endif // MP4TAG_H
