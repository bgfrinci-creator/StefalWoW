/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "ScriptedCreature.h"
#include "Vehicle.h"
#include "Position.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CellImpl.h"
#include "CombatAI.h"
#include "Containers.h"
#include "Conversation.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "MapUtils.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "PassiveAI.h"
#include "PhasingHandler.h"
#include "SpellAuras.h"
#include "SpellHistory.h"
#include "TemporarySummon.h"
#include "VehicleDefines.h"
#include "WorldStateMgr.h"

enum InDefenseOfDarkshoreData
{
    QUEST_IN_DEFENSE_OF_DARKSHORE = 13885,

    NPC_ORSEUS = 34392,
    NPC_KATHRENA_WINTERWISP_PASSENGER = 34376,
    NPC_HIPPOGRYPH_VEHICLE = 149609,

    SAY_ORSEUS_FLIGHT_START = 0
};

std::vector<Position> const DarkshoreFlightPath =
{
    Position(4983.082f, 147.904f, 54.03f, 0.0f), // 0 
    Position(4998.785f, 154.791f, 55.37f, 0.0f), // 1 
    Position(5008.601f, 151.440f, 56.12f, 0.0f), // 2 
    Position(5016.255f, 141.010f, 61.09f, 0.0f), // 3 
    Position(5030.154f, 131.867f, 59.19f, 0.0f), // 4 
    Position(5059.205f, 137.100f, 54.90f, 0.0f), // 5 
    Position(5074.855f, 136.886f, 58.72f, 0.0f), // 6 
    Position(5102.326f, 113.588f, 69.01f, 0.0f), // 7 
    Position(5110.620f, 88.3873f, 87.71f, 0.0f), // 8 
    Position(5094.453f, 64.3600f, 97.72f, 0.0f), // 9 
    Position(5045.371f, 49.3578f, 91.24f, 0.0f), // 10
    Position(5018.691f, 64.4421f, 106.8f, 0.0f), // 11
    Position(4996.760f, 111.439f, 104.2f, 0.0f), // 12
    Position(4997.118f, 135.14f, 108.23f, 0.0f), // 13
    Position(5006.433f, 169.51f, 105.19f, 0.0f), // 14
    Position(5032.296f, 209.86f, 110.53f, 0.0f), // 15
    Position(5061.362f, 196.10f, 109.26f, 0.0f), // 16
    Position(5080.187f, 192.62f, 100.93f, 0.0f), // 17
    Position(5107.658f, 208.68f, 85.210f, 0.0f), // 18
    Position(5122.117f, 214.25f, 78.088f, 0.0f), // 19
    Position(5151.975f, 183.19f, 61.492f, 0.0f), // 20
    Position(5171.787f, 143.32f, 55.759f, 0.0f), // 21
    Position(5240.819f, 112.99f, 55.129f, 0.0f), // 22
    Position(5290.197f, 127.15f, 56.697f, 0.0f), // 23
    Position(5348.519f, 158.25f, 51.441f, 0.0f), // 24
    Position(5382.229f, 156.66f, 51.246f, 0.0f), // 25
    Position(5419.743f, 131.63f, 42.334f, 0.0f), // 26
    Position(5472.857f, 126.76f, 40.022f, 0.0f), // 27
    Position(5499.018f, 130.84f, 39.913f, 0.0f), // 28
    Position(5524.263f, 104.89f, 32.294f, 0.0f), // 29
    Position(5570.366f, 96.638f, 30.671f, 0.0f), // 30
    Position(5598.000f, 107.21f, 45.935f, 0.0f), // 31
    Position(5588.744f, 149.62f, 47.852f, 0.0f), // 32
    Position(5612.548f, 194.85f, 62.083f, 0.0f), // 33
    Position(5640.354f, 250.00f, 75.895f, 0.0f), // 34
    Position(5624.089f, 298.779f, 63.97f, 0.0f), // 35
    Position(5592.600f, 335.608f, 52.71f, 0.0f), // 36
    Position(5561.638f, 337.817f, 50.81f, 0.0f), // 37
    Position(5521.916f, 317.779f, 45.89f, 0.0f), // 38
    Position(5491.415f, 324.024f, 44.28f, 0.0f), // 39
    Position(5462.579f, 347.005f, 37.10f, 0.0f), // 40
    Position(5437.134f, 336.904f, 31.27f, 0.0f), // 41
    Position(5409.680f, 328.415f, 29.44f, 0.0f), // 42
    Position(5385.230f, 353.521f, 21.92f, 0.0f), // 43
    Position(5397.919f, 385.146f, 23.90f, 0.0f), // 44
    Position(5410.269f, 428.324f, 23.72f, 0.0f), // 45
    Position(5382.372f, 444.273f, 24.28f, 0.0f), // 46
    Position(5308.930f, 478.474f, 36.03f, 0.0f), // 47
    Position(5258.018f, 374.672f, 33.97f, 0.0f), // 48
    Position(5238.927f, 306.933f, 41.86f, 0.0f), // 49
    Position(5178.771f, 305.051f, 49.13f, 0.0f), // 50
    Position(5098.464f, 307.319f, 43.84f, 0.0f), // 51
    Position(5052.391f, 319.777f, 50.32f, 0.0f), // 52
    Position(5025.717f, 347.698f, 46.53f, 0.0f), // 53
    Position(5026.339f, 375.923f, 44.18f, 0.0f), // 54
    Position(5023.440f, 413.076f, 39.35f, 0.0f), // 55
    Position(5016.427f, 451.801f, 33.18f, 0.0f), // 56
    Position(4991.187f, 456.650f, 32.72f, 0.0f), // 57
    Position(4972.034f, 438.156f, 36.36f, 0.0f), // 58
    Position(4917.539f, 434.470f, 41.54f, 0.0f), // 59
    Position(4873.733f, 431.003f, 44.19f, 0.0f), // 60
    Position(4867.322f, 418.497f, 56.18f, 0.0f), // 61
    Position(4805.276f, 394.127f, 72.29f, 0.0f), // 62
    Position(4748.263f, 357.546f, 70.85f, 0.0f), // 63
    Position(4745.722f, 313.357f, 80.13f, 0.0f), // 64
    Position(4741.031f, 259.583f, 68.07f, 0.0f), // 65
    Position(4691.104f, 249.569f, 71.48f, 0.0f), // 66
    Position(4654.592f, 298.279f, 75.80f, 0.0f), // 67
    Position(4640.235f, 343.723f, 93.64f, 0.0f), // 68
    Position(4622.934f, 421.305f, 94.50f, 0.0f), // 69
    Position(4583.104f, 474.086f, 93.55f, 0.0f), // 70
    Position(4494.966f, 464.864f, 89.91f, 0.0f), // 71
    Position(4461.783f, 404.807f, 89.07f, 0.0f), // 72
    Position(4474.378f, 364.755f, 104.3f, 0.0f), // 73
    Position(4534.314f, 312.610f, 101.5f, 0.0f), // 74
    Position(4629.545f, 275.453f, 113.1f, 0.0f), // 75
    Position(4763.200f, 219.459f, 104.1f, 0.0f), // 76
    Position(4802.652f, 155.985f, 85.80f, 0.0f), // 77
    Position(4862.660f, 101.351f, 99.08f, 0.0f), // 78
    Position(4896.81f,  94.65f,  109.01f, 0.0f), // 79
    Position(4938.95f,  84.62f,  114.26f, 0.0f), // 80
    Position(4983.93f,  96.11f,  107.05f, 0.0f), // 81
    Position(5013.88f,  121.6f,  87.380f, 0.0f), // 82
    Position(5007.40f,  150.1f,  64.509f, 0.0f), // 83
    Position(4997.12f,  156.0f,  58.538f, 0.0f), // 84
    Position(4981.38f,  152.0f,  53.367f, 0.0f)  // 85
};

// ============================================================================
// 1. NPC ORSEUS GOSSIP AI
// ============================================================================
struct npc_orseus_darkshore : public ScriptedAI
{
    npc_orseus_darkshore(Creature* creature) : ScriptedAI(creature) {}

    bool OnGossipHello(Player* player) override
    {
        if (player->GetQuestStatus(QUEST_IN_DEFENSE_OF_DARKSHORE) == QUEST_STATUS_INCOMPLETE)
        {
            AddGossipItemFor(player, GossipOptionNpc::None, "I'm ready, let's fly over Darkshore!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            SendGossipMenuFor(player, player->GetGossipTextId(me), me->GetGUID());
            return true;
        }

        SendGossipMenuFor(player, player->GetGossipTextId(me), me->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
    {
        if (gossipListId == 0)
        {
            CloseGossipMenuFor(player);

            Creature* hippogryph = me->FindNearestCreature(NPC_HIPPOGRYPH_VEHICLE, 30.0f, true);

            if (!hippogryph)
            {
                hippogryph = me->SummonCreature(NPC_HIPPOGRYPH_VEHICLE, me->GetPosition(), TEMPSUMMON_TIMED_DESPAWN, 180s);
            }

            if (hippogryph)
            {
                player->EnterVehicle(hippogryph, 0);
            }
        }
        return true;
    }
};

// ============================================================================
// 2. HIPPOGRYPH VEHICLE AI
// ============================================================================
struct npc_in_defense_of_darkshore_hippogryph : public VehicleAI
{
    npc_in_defense_of_darkshore_hippogryph(Creature* creature) : VehicleAI(creature), _summons(me) {}

    void JustAppeared() override
    {
        InitializeFlightState();
    }

    void Reset() override
    {
        if (!ObjectAccessor::GetCreature(*me, _kathrenaGUID))
        {
            InitializeFlightState();
        }
        else
        {
            me->RemoveNpcFlag(UNIT_NPC_FLAG_SPELLCLICK | UNIT_NPC_FLAG_GOSSIP);
            me->SetCanFly(true);
            me->SetDisableGravity(true);
        }
    }

    void InitializeFlightState()
    {
        me->RemoveNpcFlag(UNIT_NPC_FLAG_SPELLCLICK | UNIT_NPC_FLAG_GOSSIP);
        me->SetCanFly(true);
        me->SetDisableGravity(true);

        _currentPathIndex = 0;
        _hasStartedFlight = false;

        if (!ObjectAccessor::GetCreature(*me, _kathrenaGUID))
        {
            if (Creature* kathrena = me->SummonCreature(NPC_KATHRENA_WINTERWISP_PASSENGER, me->GetPosition(), TEMPSUMMON_MANUAL_DESPAWN, 0s))
            {
                _kathrenaGUID = kathrena->GetGUID();
                _summons.Summon(kathrena);
                kathrena->EnterVehicle(me, 1);
            }
        }
    }

    void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
    {
        if (!passenger || !passenger->IsPlayer())
            return;

        Player* player = passenger->ToPlayer();

        if (apply)
        {
            _playerGUID = player->GetGUID();
            me->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            player->SetUnitFlag(UNIT_FLAG_NON_ATTACKABLE);

            Talk(SAY_ORSEUS_FLIGHT_START, player);

            if (!_hasStartedFlight)
            {
                _hasStartedFlight = true;
                _currentPathIndex = 0;
                StartMovementToWaypoint(_currentPathIndex);
            }
        }
        else
        {
            me->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            if (Player* p = ObjectAccessor::GetPlayer(*me, _playerGUID))
            {
                p->RemoveUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
            }
            _playerGUID.Clear();

            if (_hasStartedFlight && _currentPathIndex < DarkshoreFlightPath.size())
            {
                _summons.DespawnAll();
                me->DespawnOrUnsummon(std::chrono::milliseconds(500));
            }
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE && type != EFFECT_MOTION_TYPE)
            return;

        if (id == 85)
        {
            if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGUID))
            {
                if (Quest const* quest = sObjectMgr->GetQuestTemplate(QUEST_IN_DEFENSE_OF_DARKSHORE))
                {
                    player->CompleteQuest(QUEST_IN_DEFENSE_OF_DARKSHORE);
                    player->RewardQuest(quest, (LootItemType)0, 0, me);
                }

                player->ExitVehicle();
            }

            _summons.DespawnAll();
            me->DespawnOrUnsummon(std::chrono::milliseconds(2000));
            return;
        }

        if (id == _currentPathIndex)
        {
            _currentPathIndex++;

            if (_currentPathIndex < DarkshoreFlightPath.size())
            {
            StartMovementThread:
                StartMovementToWaypoint(_currentPathIndex);
            }
        }
    }

private:
    void StartMovementToWaypoint(uint32 index)
    {
        if (index >= DarkshoreFlightPath.size())
            return;

        me->SetSpeed(MOVE_FLIGHT, 2.0f);
        me->GetMotionMaster()->MovePoint(index, DarkshoreFlightPath[index]);
    }

    bool _hasStartedFlight = false;
    uint32 _currentPathIndex = 0;
    ObjectGuid _playerGUID;
    ObjectGuid _kathrenaGUID;
    SummonList _summons;
};

// ============================================================================
// REGISTRATION
// ============================================================================
void AddSC_darkshore()
{
    RegisterCreatureAI(npc_orseus_darkshore);
    RegisterCreatureAI(npc_in_defense_of_darkshore_hippogryph);
}
