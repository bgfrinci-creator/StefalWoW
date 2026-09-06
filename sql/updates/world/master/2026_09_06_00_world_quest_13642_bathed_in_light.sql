-- Description: Fixes Quest 13642 "Bathed in Light" by adding the Spell Focus gameobject template and its world spawn at Lake Falathim (Ashenvale).

-- 1. Ensure gameobject_template exists for the Light of Elune Spell Focus
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `RequiredLevel`, `AIName`, `ScriptName`, `StringId`, `VerifiedBuild`) 
VALUES (194343, 8, 5811, 'Light of Elune Spell Focus', '', '', '', 1, 1600, 8, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', NULL, -18019);

-- 2. Clean up any existing duplicate spawns of this object in the area and insert the precise world spawn
DELETE FROM `gameobject` WHERE `id` = 194343 AND `map` = 1 AND `zoneId` = 331;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnDifficulties`, `phaseUseFlags`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `ScriptName`, `StringId`, `VerifiedBuild`) 
VALUES (11800005, 194343, 1, 331, 441, '0', 0, 0, 0, -1, 3072.88, 610.5, 5.45072, 4.75304, -0, -0, -0.692591, 0.72133, 300, 255, 1, '', NULL, 0);