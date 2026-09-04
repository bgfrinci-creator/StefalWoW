/*
 * This file is part of the Stefal WoW Project.
 * It is designed to work exclusively with the TrinityCore framework.
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
 * This code is provided for personal and educational use within the
 * Stefal WoW Project. It is not intended for commercial distribution,
 * resale, or any form of monetization.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "GameObject.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Position.h"
#include "GameObjectAI.h"
#include "TemporarySummon.h"

#include "Custom_StranglethornVale_Defines.h"


namespace Scripts::EasternKingdoms::NorthernStranglethorn
{
    struct go_kurzen_cage_204828_AI : public GameObjectAI
    {
        go_kurzen_cage_204828_AI(GameObject* obj) : GameObjectAI(obj) {}

        ObjectGuid osbornGuid;
        ObjectGuid emerineGuid;
        ObjectGuid berinnGuid;
        bool eventStarted = false;
        uint32 checkTimer = 1000;

        void Reset() override
        {
            eventStarted = false;
            osbornGuid.Clear();
            emerineGuid.Clear();
            berinnGuid.Clear();
        }

        void UpdateAI(uint32 diff) override
        {
            if (eventStarted)
                return;

            if (checkTimer <= diff)
            {
                checkTimer = 1000;

                Player* qualifiedPlayer = nullptr;
                for (auto itr = me->GetMap()->GetPlayers().begin(); itr != me->GetMap()->GetPlayers().end(); ++itr)
                {
                    Player* player = itr->GetSource();
                    if (player && me->IsWithinDist(player, 25.0f))
                    {
                        if (player->GetQuestStatus(QUEST_SPARED_FROM_MADNESS) == QUEST_STATUS_INCOMPLETE)
                        {
                            qualifiedPlayer = player;
                            break;
                        }
                    }
                }

                if (qualifiedPlayer)
                {
                    if (osbornGuid.IsEmpty())
                    {
                        Position osbornPos = { -11571.5f, -568.9f, 33.68f, 3.2f };
                        Position emerinePos = { -11570.9f, -568.55f, 33.68f, 3.2f };
                        Position berinnPos = { -11570.3f, -568.2f, 33.68f, 3.2f };

                        if (Creature* osborn = qualifiedPlayer->SummonCreature(NPC_OSBORN_OBNOTICUS, osbornPos, TEMPSUMMON_MANUAL_DESPAWN, 0ms))
                            osbornGuid = osborn->GetGUID();
                        if (Creature* emerine = qualifiedPlayer->SummonCreature(NPC_EMERINE_JUNIS, emerinePos, TEMPSUMMON_MANUAL_DESPAWN, 0ms))
                            emerineGuid = emerine->GetGUID();
                        if (Creature* berinn = qualifiedPlayer->SummonCreature(NPC_BERRIN_BURNQUILL, berinnPos, TEMPSUMMON_MANUAL_DESPAWN, 0ms))
                            berinnGuid = berinn->GetGUID();
                    }
                }
                else
                {
                    if (!osbornGuid.IsEmpty())
                    {
                        if (Creature* osborn = ObjectAccessor::GetCreature(*me, osbornGuid))
                            osborn->DespawnOrUnsummon();
                        if (Creature* emerine = ObjectAccessor::GetCreature(*me, emerineGuid))
                            emerine->DespawnOrUnsummon();
                        if (Creature* berinn = ObjectAccessor::GetCreature(*me, berinnGuid))
                            berinn->DespawnOrUnsummon();

                        osbornGuid.Clear();
                        emerineGuid.Clear();
                        berinnGuid.Clear();
                    }
                }
            }
            else
            {
                checkTimer -= diff;
            }
        }

        bool OnGossipHello(Player* player) override
        {
            if (player->GetQuestStatus(QUEST_SPARED_FROM_MADNESS) != QUEST_STATUS_INCOMPLETE)
                return false;

            if (eventStarted)
                return true;

            eventStarted = true;
            me->UseDoorOrButton();

            if (osbornGuid.IsEmpty())
            {
                Position osbornPos = { -11571.5f, -568.9f, 33.68f, 3.2f };
                Position emerinePos = { -11570.9f, -568.55f, 33.68f, 3.2f };
                Position berinnPos = { -11570.3f, -568.2f, 33.68f, 3.2f };

                if (Creature* osborn = player->SummonCreature(NPC_OSBORN_OBNOTICUS, osbornPos, TEMPSUMMON_MANUAL_DESPAWN, 0ms))
                    osbornGuid = osborn->GetGUID();
                if (Creature* emerine = player->SummonCreature(NPC_EMERINE_JUNIS, emerinePos, TEMPSUMMON_MANUAL_DESPAWN, 0ms))
                    emerineGuid = emerine->GetGUID();
                if (Creature* berinn = player->SummonCreature(NPC_BERRIN_BURNQUILL, berinnPos, TEMPSUMMON_MANUAL_DESPAWN, 0ms))
                    berinnGuid = berinn->GetGUID();
            }

            player->KilledMonsterCredit(NPC_OSBORN_OBNOTICUS);
            player->KilledMonsterCredit(NPC_EMERINE_JUNIS);
            player->KilledMonsterCredit(NPC_BERRIN_BURNQUILL);

            ObjectGuid oGuid = osbornGuid;
            ObjectGuid eGuid = emerineGuid;
            ObjectGuid bGuid = berinnGuid;

            if (Creature* osborn = ObjectAccessor::GetCreature(*player, oGuid))
            {
                osborn->SetWalk(true);
                osborn->GetMotionMaster()->MovePoint(101, -11571.2f, -572.645f, 33.6824f);
            }

            if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
            {
                emerine->SetWalk(true);
                emerine->GetMotionMaster()->MovePoint(102, -11569.4f, -573.802f, 33.6824f);
            }

            if (Creature* berinn = ObjectAccessor::GetCreature(*player, bGuid))
            {
                berinn->SetWalk(true);
                berinn->GetMotionMaster()->MovePoint(103, -11573.1f, -573.886f, 33.6826f);
            }

            player->m_Events.AddEventAtOffset([oGuid, eGuid, bGuid, player]()
                {
                    if (Creature* osborn = ObjectAccessor::GetCreature(*player, oGuid))
                    {
                        osborn->GetMotionMaster()->Clear();
                        osborn->SetFacingTo(4.72109f);
                    }

                    if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
                    {
                        emerine->GetMotionMaster()->Clear();
                        emerine->SetFacingTo(3.16992f);
                    }

                    if (Creature* berinn = ObjectAccessor::GetCreature(*player, bGuid))
                    {
                        berinn->GetMotionMaster()->Clear();
                        berinn->SetFacingTo(0.060213f);
                    }
                }, 3500ms);

            player->m_Events.AddEventAtOffset([oGuid, player]()
                {
                    if (Creature* osborn = ObjectAccessor::GetCreature(*player, oGuid))
                        osborn->AI()->Talk(0);
                }, 4000ms);

            player->m_Events.AddEventAtOffset([bGuid, player]()
                {
                    if (Creature* berinn = ObjectAccessor::GetCreature(*player, bGuid))
                        berinn->AI()->Talk(0);
                }, 5000ms);

            player->m_Events.AddEventAtOffset([eGuid, player]()
                {
                    if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
                        emerine->AI()->Talk(0);
                }, 7000ms);

            player->m_Events.AddEventAtOffset([eGuid, player]()
                {
                    if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
                        emerine->AI()->Talk(1);
                }, 9000ms);

            player->m_Events.AddEventAtOffset([eGuid, player]()
                {
                    if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
                        emerine->AI()->Talk(2);
                }, 11000ms);

            player->m_Events.AddEventAtOffset([oGuid, eGuid, bGuid, player]()
                {
                    if (Creature* osborn = ObjectAccessor::GetCreature(*player, oGuid))
                        osborn->CastSpell(osborn, SPELL_TELEPORT, true);
                    if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
                        emerine->CastSpell(emerine, SPELL_TELEPORT, true);
                    if (Creature* berinn = ObjectAccessor::GetCreature(*player, bGuid))
                        berinn->CastSpell(berinn, SPELL_TELEPORT, true);
                }, 14000ms);

            player->m_Events.AddEventAtOffset([this, oGuid, eGuid, bGuid, player]()
                {
                    if (Creature* osborn = ObjectAccessor::GetCreature(*player, oGuid))
                        osborn->DespawnOrUnsummon(0ms, 0s);
                    if (Creature* emerine = ObjectAccessor::GetCreature(*player, eGuid))
                        emerine->DespawnOrUnsummon(0ms, 0s);
                    if (Creature* berinn = ObjectAccessor::GetCreature(*player, bGuid))
                        berinn->DespawnOrUnsummon(0ms, 0s);

                    eventStarted = false;
                    osbornGuid.Clear();
                    emerineGuid.Clear();
                    berinnGuid.Clear();
                }, 15000ms);

            return true;
        }
    };

    class go_kurzen_cage_204828 : public GameObjectScript
    {
    public:
        go_kurzen_cage_204828() : GameObjectScript("go_kurzen_cage_204828") {}

        GameObjectAI* GetAI(GameObject* go) const override
        {
            return new go_kurzen_cage_204828_AI(go);
        }
    };
}

void AddSC_zone_northern_stranglethorn()
{
    using namespace Scripts::EasternKingdoms::NorthernStranglethorn;
    new go_kurzen_cage_204828();
}
