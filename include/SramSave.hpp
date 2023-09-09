#pragma once

#include <bn_string_view.h>

namespace cr
{

class SramSave
{
public:
    static constexpr bn::string_view MAGIC_STR = "crsg000";

public:
    SramSave();

    int read_song_index();
    void write_song_index(int song_index);

private:
    char _magic_str[8];
    int _song_index;
};

} // namespace cr
