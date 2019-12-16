#include "profile.h"

extern struct ee_prom EEPROM;

struct profile Profile = {
    .data = {
        .name = {},
        .loss = 0,
        .wins = 0,
        .type = SLAVE
    },
    .eeprom_addr        = 0x0F,
    ._save              = profile_save,
    .load               = profile_load,
    .toggle_spi_mode    = profile_toggle_spi_mode,
    .reset_data         = profile_reset_data
};

void profile_load()
{    
    EEPROM.read_buffer(Profile.eeprom_addr, &Profile.data, sizeof(Profile.data));

    if (Profile.data.name[15] || !Profile.data.name[0])
        Profile.reset_data();
}

void profile_save()
{
    EEPROM.write_buffer(Profile.eeprom_addr, &Profile.data, sizeof(Profile.data));
}

void profile_toggle_spi_mode()
{
    Profile.data.type = Profile.data.type == MASTER ? SLAVE : MASTER;
}

void profile_reset_data()
{
    char default_name[16] = "Player";
    int idx;
    
    for (idx = 0; default_name[idx]; idx++)
        Profile.data.name[idx] = default_name[idx];
    while (idx < 16)
        Profile.data.name[idx++] = 0;

    Profile.data.wins = 0;
    Profile.data.loss = 0;

    Profile.data.type = SLAVE;
}