#include "SonarEngine/Buffers/AudioListenersBuffer.h"

namespace SonarEngine {
	AudioListenersBuffer::AudioListenersBuffer(size_t initialBufferSize) :
		TSystemData("AudioListenersBuffer", initialBufferSize) {}

	AudioListener& AudioListenersBuffer::CreateAudioListener() {
	    _data.emplace_back(std::unique_ptr<AudioListener>(new AudioListener()));
	
		if (ActiveAudioListener == nullptr) {
			ActiveAudioListener = _data.back().get();
			ActiveAudioListener->SetActive(true);
		}

	    return *_data.back().get();
	}

	void AudioListenersBuffer::SetActiveAudioListener(AudioListener& listener) {
		//checking audio listener
	
		bool finded = false;
	
		for (auto& checkedListener : GetAllData()) {
			if (checkedListener.get() == &listener) {
				finded = true;
				break;
			}
		}
	
		if (finded) {
			//reset active listeners
			for (auto& checkedListener : GetAllData()) {
				checkedListener->SetActive(false);
			}
	
			ActiveAudioListener = &listener;
			listener.SetActive(true);
		}
	}
}