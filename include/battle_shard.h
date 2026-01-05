#ifndef GUARD_BATTLE_SHARD_H
#define GUARD_BATTLE_SHARD_H

void ActivateShard(u32 battler);
bool32 CanActivateShard(u32 battler);
enum Ability GetBattlerShardAbility(u32 battler);
void UpdateDisplayedShardAbility(u32 battler);

#endif
