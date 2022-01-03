#pragma once

enum class cell_type_enum { Empty = 0, Barrier, Enemy, Gateway, Npc, Player };
enum class locations_enum { None = 0, The_Commons, Headmaster_Ambrose_Office, Ravenwood, Unicorn_Way };
enum class school_enum { None = 0, Fire, Ice, Storm, Myth, Life, Death, Balance };
enum class spell_type_enum { None = 0, Damage, Healing, Necromancy, Ward, Charm, Global, Manipulation, Enchantment };
enum class orientation_enum { None = 0, Horizontal, Vertical };