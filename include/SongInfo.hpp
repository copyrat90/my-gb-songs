#pragma once

#include <bn_array.h>
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
    bn::array<bn::string_view, 4> description;
};

} // namespace cr
