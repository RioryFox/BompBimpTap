#define PARTS_COUNT

class dinamic {
        public:
                int *parts [PARTS_COUNT];
                uint16_t min_Hz;
                uint16_t max_Hz;
                uint8_t Volume;
                int count(int got_sound, int dinamic_sound) {
                        int result = (got_sound - dinamic_sound);
                        return result;
                };
};

class groupOfDinamic {
        public:
                char name[3];  

                explictic groupOfDinamic(char groupName) : name(groupName){}
                
                std::size_t add_dinamic() {
                        speakers.emplace_back();
                        return speakers.size() - 1;
                };

                dinamic& get_dinamic(std::size_t index) {
                        return speakers[index];
                };

                std::size_t count() const {
                        return speakers.size();
                };
        
        private:
                std::vector<dinamic> speakers;
};