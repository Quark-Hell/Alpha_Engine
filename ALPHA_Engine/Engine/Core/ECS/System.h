#pragma once
#include <vector>
#include <string>
#include "Core/ECS/SystemData.h"

namespace Core {
  class World;

  class System {
  protected:
    friend class World;

    std::vector<std::string> _tokens;
    const size_t _order;

    /*
     Use tokens to get System Data

     For example, if you create render engine, you should get buffer with meshes
     So you can initialize it like this:
     std::vector<std::string> tokens{"MeshData"}
     Now core automatically find data with this token and push this into system

     Also I recommended set order with shift 100
     It allows another modules integrate into your system logic
    */

    System(const std::vector<std::string> &tokens, const size_t order);
    System() = delete;

    //virtual void Init() = 0;
    virtual void EntryPoint(std::vector<Core::SystemData*>& data) = 0;

  public:
    virtual ~System() = default;

    const std::vector<std::string>& GetTokens();

    System(const System&) = delete;
    System& operator=(const System&) = delete;
    System(System&&) = delete;
    System& operator=(System&&) = delete;
  };
}
