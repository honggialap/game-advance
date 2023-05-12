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

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <memory>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include <thread>
#include <mutex>
#include <queue>
#include <tuple>
#include <map>
#include <sstream>
#include <cmath>

#define PIXEL_PER_METER 30.0f
#define MAX_PACKET_SIZE 65535

#define SCENE_TYPE_LOBBY	1
#define SCENE_TYPE_WORLD	2

#define ACTOR_TYPE_TANK		1
#define ACTOR_TYPE_BULLET	2
#define ACTOR_TYPE_WALL		3

#endif // !__ENGINE_COMMON_H__
