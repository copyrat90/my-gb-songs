#include "SramSave.hpp"

#include <bn_cstring.h>
#include <bn_sram.h>

#include "SongKind.hpp"

namespace cr
{

SramSave::SramSave() : _song_index(0)
{
    for (int i = 0; i < MAGIC_STR.size(); ++i)
        _magic_str[i] = MAGIC_STR[i];
}

int SramSave::read_song_index()
{
    bn::sram::read(*this);

    if (bn::string_view(_magic_str) != MAGIC_STR || !(0 <= _song_index && _song_index < (int)SongKind::TOTAL_COUNT))
    {
        bn::memclear(_magic_str, 8);
        for (int i = 0; i < MAGIC_STR.size(); ++i)
            _magic_str[i] = MAGIC_STR[i];

        _song_index = 0;
    }

    return _song_index;
}

void SramSave::write_song_index(int song_index)
{
    _song_index = song_index;

    bn::sram::write(*this);
}

} // namespace cr
