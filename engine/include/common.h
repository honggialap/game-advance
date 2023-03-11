#pragma once
#ifndef __ENGINE_COMMON_H__
#define __ENGINE_COMMON_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <box2d/box2d.h>

#include <json.hpp>

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include <thread>

#endif // !__ENGINE_COMMON_H__
