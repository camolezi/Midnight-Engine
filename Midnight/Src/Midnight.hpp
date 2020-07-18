#ifndef MIDNIGHTH_HPP
#define MIDNIGHTH_HPP

//For client application to include

//Events
#include <eventMacro.hpp>

//Debug
#include <debug.hpp>

//Math
#include <coreMath.hpp>

//Application
#include <midnightApplication.hpp>

//input
#include <key.hpp>
#include <mouseButton.hpp>
#include <input.hpp>

//Render
#include <renderer2D.hpp>
#include <transform.hpp>

//Audio
#include <audioEngine.hpp>

//Time
#include <time.hpp>

//UI iamGUI(only temporary)
#include <imgui.h>
#include <imGuiAbstraction.hpp>

#include <memory>

//using Camera = std::shared_ptr<MN::Sound>;

namespace MN{
    template<typename T>
    using Var = std::shared_ptr<T>;
}

#endif
