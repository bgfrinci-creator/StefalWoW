-- ============================================================================
-- COMPLETE DATABASE BUNDLE FOR QUEST 55639 & 59949: "WHO LURKS IN THE PIT"
-- ============================================================================
SET NAMES utf8mb4;

-- 0. CLEANUP STATIC WORLD SPAWNS
DELETE FROM `creature` WHERE `id` IN (156900, 156902, 167250);

-- 1. CREATURE TEMPLATES
DELETE FROM `creature_template` WHERE `entry` IN (156900, 156902, 156929, 160964, 167250, 167254);

INSERT INTO `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `name`, `femaleName`, `subname`, `TitleAlt`, `IconName`, `RequiredExpansion`, `VignetteID`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `Classification`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `BaseVariance`, `RangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `unit_flags3`, `family`, `trainer_class`, `type`, `VehicleId`, `AIName`, `MovementType`, `ExperienceModifier`, `RacialLeader`, `movementId`, `WidgetSetID`, `WidgetSetUnitConditionID`, `RegenHealth`, `CreatureImmunitiesId`, `flags_extra`, `ScriptName`, `StringId`, `VerifiedBuild`) VALUES 
(156900, 0, 0, 'Hrun the Exiled', '', NULL, NULL, NULL, 0, 0, 14, 0, 1, 1.35714, 1, 0, 0, 2000, 2000, 1, 1, 2, 0, 2048, 0, 0, 0, 6, 0, '', 0, 1, 0, 875, 0, 0, 1, 0, 0, 'npc_hrun_q55639', NULL, 56313),
(156902, 0, 0, 'Ralia Dreamchaser', '', NULL, NULL, NULL, 0, 0, 0, 0, 1, 1.14286, 1, 0, 0, 0, 2000, 1, 1, 8, 0, 0, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_ralia_prisoner', 'ralia_dreamchaser_prisoner', 56313),
(156929, 0, 0, 'Ralia Dreamchaser', '', NULL, NULL, 'vehichlecursor', 0, 0, 2142, 33554432, 1, 1.14286, 1, 0, 0, 0, 2000, 1, 1, 8, 0, 2048, 67108864, 5, 0, 1, 6832, '', 0, 1, 0, 206, 0, 0, 1, 0, 0, 'npc_ralia_vehicle_q55639', NULL, 56313),
(160964, 0, 0, 'Freed Expedition Member', '', NULL, NULL, NULL, 0, 0, 0, 0, 1, 1.14286, 1, 0, 0, 0, 2000, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_freed_expedition_member_q55639', NULL, 56313),
(167254, 0, 0, 'Crenna Earth-Daughter', '', NULL, NULL, 'vehichlecursor', 0, 0, 2361, 33554432, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 8, 0, 2048, 67108864, 0, 0, 7, 6832, '', 0, 1, 0, 206, 0, 0, 1, 0, 0, 'npc_ralia_vehicle_q55639', NULL, 66384),
(167250, 0, 0, 'Crenna Earth-Daughter', '', NULL, NULL, NULL, 0, 0, 2361, 0, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 1, 0, 2048, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_ralia_prisoner', NULL, 66384);


-- 2. QUEST TEMPLATE ADDON (Quest Script Registration for Both Factions)
INSERT INTO `quest_template_addon` (`ID`, `MaxLevel`, `AllowableClasses`, `SourceSpellID`, `PrevQuestID`, `NextQuestID`, `ExclusiveGroup`, `BreadcrumbForQuestID`, `ProvidedItemCount`, `SpecialFlags`, `ScriptName`) VALUES 
(55639, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'q55639_who_lurks_in_the_pit'),
(59949, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'q55639_who_lurks_in_the_pit')
ON DUPLICATE KEY UPDATE `ScriptName` = 'q55639_who_lurks_in_the_pit';


-- 3. QUEST METADATA & BUILD UPDATES
UPDATE `quest_template` SET `VerifiedBuild` = 56313 WHERE `ID` = 55639;
UPDATE `quest_details` SET `VerifiedBuild` = 56313 WHERE `ID` = 55639;
UPDATE `quest_offer_reward` SET `VerifiedBuild` = 56313 WHERE `ID` = 55639;

UPDATE `quest_poi` SET `VerifiedBuild` = 56313 WHERE (`QuestID` = 55639 AND `BlobIndex` = 0 AND `Idx1` = 4) 
    OR (`QuestID` = 55639 AND `BlobIndex` = 0 AND `Idx1` = 3) 
    OR (`QuestID` = 55639 AND `BlobIndex` = 0 AND `Idx1` = 2) 
    OR (`QuestID` = 55639 AND `BlobIndex` = 0 AND `Idx1` = 1) 
    OR (`QuestID` = 55639 AND `BlobIndex` = 0 AND `Idx1` = 0);

UPDATE `quest_poi_points` SET `VerifiedBuild` = 56313 WHERE (`QuestID` = 55639 AND `Idx1` = 4 AND `Idx2` = 0) 
    OR (`QuestID` = 55639 AND `Idx1` = 3 AND `Idx2` = 0) 
    OR (`QuestID` = 55639 AND `Idx1` = 2 AND `Idx2` = 0) 
    OR (`QuestID` = 55639 AND `Idx1` = 1 AND `Idx2` = 4) 
    OR (`QuestID` = 55639 AND `Idx1` = 1 AND `Idx2` = 3) 
    OR (`QuestID` = 55639 AND `Idx1` = 1 AND `Idx2` = 2) 
    OR (`QuestID` = 55639 AND `Idx1` = 1 AND `Idx2` = 1) 
    OR (`QuestID` = 55639 AND `Idx1` = 1 AND `Idx2` = 0) 
    OR (`QuestID` = 55639 AND `Idx1` = 0 AND `Idx2` = 0);


-- 4. QUEST STARTER & ENDER RELATIONS
DELETE FROM `creature_queststarter` WHERE (`id` IN (167225, 167226) AND `quest` = 55639) OR (`id` = 156803 AND `quest` = 59949);
DELETE FROM `creature_questender` WHERE (`id` IN (167225, 167226) AND `quest` = 55639) OR (`id` = 156807 AND `quest` = 59949);

REPLACE INTO `creature_queststarter` (`id`, `quest`, `VerifiedBuild`) VALUES (156803, 55639, 56313);
REPLACE INTO `creature_questender` (`id`, `quest`, `VerifiedBuild`) VALUES (156807, 55639, 56313);

REPLACE INTO `creature_queststarter` (`id`, `quest`, `VerifiedBuild`) VALUES 
(167225, 59949, 66384),
(167226, 59949, 66384);

REPLACE INTO `creature_questender` (`id`, `quest`, `VerifiedBuild`) VALUES 
(167225, 59949, 66384),
(167226, 59949, 66384);


-- 5. CREATURE TEXTS
DELETE FROM `creature_text` WHERE `CreatureID` IN (156900, 156891, 156902, 156803, 156929, 160964, 167250, 167254);

INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundPlayType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES 
(156900, 0, 0, 'I will harvest your life force... and then those who sealed me in here will burn.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Hrun - Agro'),
(156900, 1, 0, 'If... I die... so... do you!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Hrun - Death'),
(156900, 2, 0, 'You will be kindling for the flame!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Hrun - Say to Prisoner / Objective Reached'),
(156891, 2, 0, 'The survivors are counting on ya!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Bjorn - Accept Quest'),
(156891, 3, 0, 'You did a good job saving those people and dealing with those spiders.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Bjorn - Post Escape 1'),
(156891, 4, 0, 'Yeah…well, I guess ye could see it that way.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Bjorn - Post Escape 2'),
(156891, 5, 0, 'Bah! You were just telling me how much you hate spiders.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Bjorn - Post Escape 3'),
(156902, 0, 0, 'Is anyone there? Help! Elune, guide them to me!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Ralia Prisoner - Objective Reached'),
(156902, 1, 0, 'You saved my life! Allow me to return the favor! Hop on!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Ralia Prisoner - Freed / Thank You'),
(156902, 2, 0, 'Those spiders were victims too. They just lost their home.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Ralia - Post Escape Spiders'),
(156803, 0, 0, 'Rescue anyone you can!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Alaria - Accept Quest'),
(156803, 1, 0, 'By the Light you’re alive!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Alaria - Post Escape 1'),
(156803, 2, 0, 'You should have known better than to say that to a druid.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Alaria - Post Escape 2'),
(156803, 3, 0, 'The Light shines on all creatures. That does not mean I have to like them.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Alaria - Post Escape 3'),
(156929, 0, 0, 'Elune, please shield us from harm!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Ralia Vehicle - Escape Start'),
(160964, 0, 0, 'I though I was dead! Please, you have to rescue Ralia Dreamchaser deeper below!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Trapped Guard - Freed'),
(167250, 0, 0, 'A rescue party! Earth Mother, guide their path!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Crenna Prisoner - Objective Reached'),
(167250, 1, 0, 'Thank you, friend. I will bear us to safety. Hop on!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Crenna Prisoner - Freed / Thank You'),
(167250, 2, 0, 'Those spiders had their rightful home destroyed. They deserved better.', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Crenna - Post Escape Spiders'),
(167254, 0, 0, 'An\'she, watch over and protect us!', 12, 0, 100, 0, 0, 0, 0, 0, 0, 'Crenna Vehicle - Escape Start');


-- 6. GAMEOBJECT STATE CONFIGURATION
UPDATE `gameobject` SET `state` = 1 WHERE `id` IN (339568, 350796);


-- 7. VEHICLE SPELLCLICK CONFIGURATION
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (156929, 167254);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES 
(156929, 43671, 1, 0),
(167254, 43671, 1, 0);


-- 8. HORDE GAMEOBJECT SPAWNS (Thick Cocoon - Entry 350796)
DELETE FROM `gameobject` WHERE `id` = 350796 AND `guid` BETWEEN 9500001 AND 9500005;

INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `StringId`, `VerifiedBuild`) VALUES 
(9500001, 350796, 2175, 10424, 10527, '0', 0, 15337, 0, -1, 80.4809, -2279.52, 60.4192, 0.0210855, -0.090744, 0.175645, 0.0263472, 0.979908, 120, 255, 1, '', NULL, 66102),
(9500002, 350796, 2175, 10424, 10527, '0', 0, 15337, 0, -1, 36.0295, -2199.45, 17.0092, 2.1421, -0.197591, 0.0066061, 0.867941, 0.455624, 120, 255, 1, '', NULL, 66102),
(9500003, 350796, 2175, 10424, 10527, '0', 0, 15337, 0, -1, 123.569, -2238.92, -5.86077, 1.35752, -0.0759168, -0.0817127, 0.622531, 0.774606, 120, 255, 1, '', NULL, 66102),
(9500004, 350796, 2175, 10424, 10527, '0', 0, 15337, 0, -1, 111.057, -2217.92, 32.9515, 2.87513, -0.186835, -0.064641, 0.973573, 0.114326, 120, 255, 1, '', NULL, 66102),
(9500005, 350796, 2175, 10424, 10527, '0', 0, 15337, 0, -1, 65.342, -2276.59, -0.662279, 0.820588, -0.151949, 0.12648, 0.40564, 0.892396, 120, 255, 1, '', NULL, 66102);