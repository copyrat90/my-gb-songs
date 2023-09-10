#include "SongInfo.hpp"

#include "SongKind.hpp"

#include "bn_dmg_music_items_hell_owo_rld.h"

namespace cr
{

static constexpr SongInfo SONGS[(int)SongKind::TOTAL_COUNT] = {
    SongInfo{
        bn::dmg_music_items::hell_owo_rld,
        "hellOWOrld",
        {
            "First loop I wrote in FamiTracker years ago,",
            "later converted into hUGETracker format.",
            "Mostly inspired by Kitsune^2 - Naradno,",
            "Pachelbel - Canon in D and few other songs.",
        },
    },
};

auto SongInfo::get(SongKind kind) -> const SongInfo&
{
    BN_ASSERT(0 <= (int)kind && (int)kind < (int)SongKind::TOTAL_COUNT);

    return SONGS[(int)kind];
}

} // namespace cr
