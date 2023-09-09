#pragma once

#include <bn_string_view.h>

namespace bn
{
class dmg_music_item;
}

namespace cr
{

enum class SongKind;

struct SongInfo
{
public:
    static auto get(SongKind) -> const SongInfo&;

public:
    const bn::dmg_music_item& song;
    bn::string_view title;
    bn::string_view license_str;
};

} // namespace cr
