class TimeOfDay {
public:
    unsigned char hour{}, minute{}, second{};

    TimeOfDay(unsigned char h, unsigned char m, unsigned char s) : hour(h), minute(m), second(s) {}

    bool IsAM() const {
        return IsValid() && (hour < 12);
    }

    bool IsPM() const {
        return IsValid() && (hour >= 12);
    }

    bool IsValid() const {
        return (hour < 24) && (minute < 60) && (second < 60);
    }

    bool operator < (const TimeOfDay &rhs)const{
        if (hour == rhs.hour){
            if (minute == rhs.minute)return second < rhs.second;
            else return minute < rhs.minute;
        }else return hour < rhs.hour;
    }

    bool operator > (const TimeOfDay &rhs)const{
        if (hour == rhs.hour){
            if (minute == rhs.minute)return second > rhs.second;
            else return minute > rhs.minute;
        }else return hour > rhs.hour;
    }

    bool operator == (const TimeOfDay &rhs)const{
        return hour==rhs.hour && minute==rhs.minute && second==rhs.second;
    }


};
namespace std {
    template<> struct hash<TimeOfDay>
    {
        std::size_t operator()(const TimeOfDay& p) const noexcept
        {
            return p.hour + p.minute<<8 + p.second<<16;
        }
    };
}

