#pragma once

#include "TSerialized.h"

#include "Core/Serialization/Serialized.h"

namespace Core {

    template <typename T>//, typename = std::enable_if_t<std::is_base_of_v<Serialized,T>, bool>>
    class TSerialized : public Serialized {

    public:
        //This serializes data into local buffer
        void Serialize(const T& data) {
            _size = bitsery::quickSerialization<bitsery::OutputBufferAdapter<Buffer>>(_buffer, data);
        }

        //This deserializes data into T& input from local buffer
        void Deserialize(T& input) {
            if (_buffer.empty()) {
                Logger::LogError("Buffer is empty, you should previously use TSerialized<T>::Serialize function: " + __LOGERROR__);
            }

            auto state = bitsery::quickDeserialization<bitsery::InputBufferAdapter<Buffer>>({_buffer.begin(), _size}, input);
            assert(state.first == bitsery::ReaderError::NoError && state.second);
        }

        //This saved data into file by path
        static void SaveData(T& data, std::string& path) {
            if (path.empty()) {
                Logger::LogError("path is empty: " + __LOGERROR__);
                return;
            }

            std::string realPath = std::filesystem::current_path().string() + path;

#ifdef WINDOWS
            std::replace(realPath.begin(), realPath.end(), '/', '\\');
#else
            std::replace(realPath.begin(), realPath.end(), '\\', '/');
#endif

           std::fstream stream{ realPath, std::fstream::binary | std::fstream::trunc | std::fstream::out};
           if (!stream.is_open()) {
               Logger::LogError("Cannot open file by path:", realPath + ":" + __LOGERROR__);
               return;
           }

           bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> ser{ stream };
           ser.object(data);
           ser.adapter().flush();
           stream.close();
        }




        static void LoadData(T& data, std::string& path) {
            if (path.empty()) {
                Logger::LogError("path is empty: " + __LOGERROR__);
                return;
            }

            std::string realPath = std::filesystem::current_path().string() + path;

#ifdef WINDOWS
            std::replace(realPath.begin(), realPath.end(), '/', '\\');
#else
            std::replace(realPath.begin(), realPath.end(), '\\', '/');
#endif

            std::fstream stream{ realPath, std::fstream::binary | std::fstream::in };
            if (!stream.is_open()) {
                Logger::LogError("Cannot open file by path:", realPath + ":" + __LOGERROR__);
                return;
            }

            /*auto state =*/ bitsery::quickDeserialization<bitsery::InputStreamAdapter>(stream, data);
            //assert(state.first == bitsery::ReaderError::NoError && state.second);
        }

    };

}

