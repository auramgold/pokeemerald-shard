#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_shard.h"
#include "battle_gimmick.h"
#include "battle_scripts.h"
#include "event_data.h"
#include "item.h"
#include "palette.h"
#include "pokemon.h"
#include "safari_zone.h"
#include "sprite.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/rgb.h"

// Sets flags and variables upon a battler's Shard Activation.
void ActivateShard(u32 battler)
{
	// Set appropriate flags.
	SetActiveGimmick(battler, GIMMICK_SHARD);
	SetGimmickAsActivated(battler, GIMMICK_SHARD);

	// Update and execute changed ability.
	UpdateDisplayedShardAbility(battler);
	gSpecialStatuses[battler].switchInAbilityDone = FALSE;

	// Execute battle script.
	PREPARE_ABILITY_BUFFER(gBattleTextBuff1, GetBattlerShardAbility(battler));
	BattleScriptExecute(BattleScript_ShardShattering);
}

// Returns whether a battler can Terastallize.
bool32 CanActivateShard(u32 battler)
{
	// Check if Trainer has already Shattered.
	if (HasTrainerUsedGimmick(battler, GIMMICK_SHARD))
		return FALSE;

	// Check if AI battler is intended to Shattered.
	/*if (!ShouldTrainerBattlerUseGimmick(battler, GIMMICK_SHARD))
		return FALSE;*/
	//TODO: Setup AI use of Shards

	// Check if battler has another gimmick active.
	if (GetActiveGimmick(battler) != GIMMICK_NONE)
		return FALSE;

	// Check if battler has a set shard ability.
	if (GetBattlerShardAbility(battler) == ABILITY_NONE)
		return FALSE;

	// Every check passed!
	return TRUE;
}

// Returns a battler's Shard Ability.
enum Ability GetBattlerShardAbility(u32 battler)
{
	return GetMonData(GetBattlerMon(battler), MON_DATA_SHARD_ABILITY);
}

void UpdateDisplayedShardAbility(u32 battler)
{
	if(GetActiveGimmick(battler) == GIMMICK_SHARD)
		gBattleMons[battler].ability = GetBattlerShardAbility(battler);
}
