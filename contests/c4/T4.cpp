#include <string>

struct handle_t{
    handle_t(handle_t& h){

    }


    handle_t(){

    }
};

const handle_t kNullHandle;

void raw_write(handle_t handle, const std::string& content){};
void raw_close(handle_t handle){};



class IOWrapper{
private:
    handle_t handle;
public:

    IOWrapper()= delete;

    IOWrapper(const IOWrapper& wrapper)= delete;

    IOWrapper operator = (const IOWrapper& wrapper)= delete;

    IOWrapper(handle_t&& v) noexcept {
        handle=v;
        v=kNullHandle;
    }

    IOWrapper(IOWrapper&& v) noexcept {
        handle=v.handle;
        v.handle=kNullHandle;
    }

    IOWrapper& operator = (IOWrapper&& v){
        handle = v.handle;
        v.handle = kNullHandle;
        return *this;
    }

    ~IOWrapper(){
        if (this->handle!=kNullHandle)raw_close(this->handle);
    }

    void Write(const std::string& content){
        if (this->handle != kNullHandle)raw_write(this->handle, content);
    }
};

handle_t get(){
    handle_t w;
    return w;
}

int main(){
    IOWrapper a();
    IOWrapper ai1(get());
    ai1=get();
    return 0;
}