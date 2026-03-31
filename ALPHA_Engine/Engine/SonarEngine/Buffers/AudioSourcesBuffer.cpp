#include "SonarEngine/Buffers/AudioSourcesBuffer.h"

namespace SonarEngine {
	AudioSourcesBuffer::AudioSourcesBuffer(size_t initialBufferSize) : TSystemData("AudioSourcesBuffer", initialBufferSize) {}

    AudioSource& AudioSourcesBuffer::CreateAudioSource() {
        _data.emplace_back(std::unique_ptr<AudioSource>(new AudioSource()));

        return *_data.back().get();
    }
}