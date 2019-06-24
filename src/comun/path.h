
#ifndef PATH_H
#define PATH_H

#ifdef DEBUG
#define CONFIG ""
#define ASSETS ""
#define MAPAS ""
#else
#define CONFIG "/etc/Portal/"
#define ASSETS "/var/Portal/"
#define MAPAS "/var/Portal/"
#endif

#endif //PATH_H
