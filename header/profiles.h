#ifndef AUDIO_PROFILES
#define AUDIO_PROFILES_BASS
#define AUDIO_PROFILES_MEDIUM
#define AUDIO_PROFILES_VOCAL
wchar_t AUDIO_PROFILES, AUDIO_PROFILES_BASS, AUDIO_PROFILES_MEDIUM, AUDIO_PROFILES_VOCAL;

struct AudioSpeaker {
        wchar_t min_Hz; //wchar_t взят потому что слух человека работает от 20Гц до 20 000Гц, а тут до 65535 можно хранить
        wchar_t max_Hz;
        unsigned char Volume;
        bool OnOrOff;
        bool LeftOrRight; //0 - it is left, 1 - it is Right - это временное размышление, фактически будут классы
} AUDIO_PROFILES_BASS, AUDIO_PROFILES_MEDIUM, AUDIO_PROFILES_VOCAL;

struct AudioSpeakersGroup {
        struct AudioSpeaker AUDIO_PROFILES_BASS;
        struct AudioSpeaker AUDIO_PROFILES_MEDIUM;
        struct AudioSpeaker AUDIO_PROFILES_VOCAL;
} AUDIO_PROFILES;

#endif 