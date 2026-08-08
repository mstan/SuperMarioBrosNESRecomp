#include "mod_audio.h"

#include <stdint.h>
#include <stdio.h>

static int expect_sample(const char *label, int16_t have, int16_t want)
{
    if (have == want) return 1;
    fprintf(stderr, "FAIL %s: have %d, want %d\n", label, (int)have, (int)want);
    return 0;
}

int main(void)
{
    static const int16_t sequence[] = { 1000, -1000, 30000 };
    static const int16_t loud[] = { 30000 };
    int16_t out[4] = { 0, 0, 0, 0 };
    NESModAudioClip clip = nes_mod_audio_register_pcm_s16_mono(sequence, 3);
    NESModAudioClip loud_clip = nes_mod_audio_register_pcm_s16_mono(loud, 1);
    int ok = clip != 0 && loud_clip != 0;

    ok &= nes_mod_audio_play(clip, 100);
    nes_mod_audio_mix(out, 2);
    ok &= expect_sample("sequence[0]", out[0], 1000);
    ok &= expect_sample("sequence[1]", out[1], -1000);
    nes_mod_audio_mix(out + 2, 2);
    ok &= expect_sample("sequence[2]", out[2], 30000);
    ok &= expect_sample("ended voice", out[3], 0);

    out[0] = 0;
    ok &= nes_mod_audio_play(loud_clip, 100);
    ok &= nes_mod_audio_play(loud_clip, 100);
    nes_mod_audio_mix(out, 1);
    ok &= expect_sample("saturating overlap", out[0], 32767);

    out[0] = 0;
    ok &= nes_mod_audio_play(clip, 100);
    nes_mod_audio_stop_all();
    nes_mod_audio_mix(out, 1);
    ok &= expect_sample("stop all", out[0], 0);

    nes_mod_audio_unregister(clip);
    ok &= !nes_mod_audio_play(clip, 100);
    nes_mod_audio_unregister(loud_clip);

    if (ok) printf("mod_audio: registration, mix, saturation, stop, unregister OK\n");
    return ok ? 0 : 1;
}
