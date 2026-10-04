#include "profiles.h"
#include <iostream>

class AudioProfile {
        public:
                struct AudioSpeakersGroup Audio;
                AudioProfile (){
                        std::cout << "\r\nInitial success!\r\n";
                        Audio.AUDIO_PROFILES_BASS.min_Hz = 20;
                        std::cout << Audio.AUDIO_PROFILES_BASS.min_Hz << "\r\n";
                };
};