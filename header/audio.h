#include "profiles.h"
#include <iostream>

class AudioProfile {
        public:
                struct AudioSpeakersGroup Audio;
                AudioProfile (){
                        std::cout << "\r\ntest sucsess!\r\n";
                };
};