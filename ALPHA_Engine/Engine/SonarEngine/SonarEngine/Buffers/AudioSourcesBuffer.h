#pragma once

#include "SonarEngine/Components/AudioSource.h"
#include "Core/ECS/TSystemData.h"

namespace SonarEngine {
    class AudioSourcesBuffer final : public Core::TSystemData<AudioSource> {
        friend class SonarEngine;

    public:
        AudioSourcesBuffer(size_t initialBufferSize = 0);
        ~AudioSourcesBuffer() override = default;

        AudioSource& CreateAudioSource();
    };
}

