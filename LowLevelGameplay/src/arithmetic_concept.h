#pragma once
#include <concepts>
#include "Component.h"

template<class T>
concept isComponent = std::derived_from<T, Component> == true;

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;
