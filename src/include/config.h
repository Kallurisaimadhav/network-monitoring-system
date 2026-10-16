#ifndef CONFIG_H
#define CONFIG_H

extern int refresh_time;

extern int cpu_alert;
extern int memory_alert;
extern int disk_alert;

void config_init(void);

#endif
