-- Quest: Spared from Madness (26736) - Kurzen Cage & NPC Texts Fix

-- 1. GameObject Template configuration for Kurzen Cage
DELETE FROM `gameobject_template` WHERE `entry` = 204828;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `size`, `Data0`, `Data1`, `Data2`, `Data3`, `Data4`, `Data5`, `Data6`, `Data7`, `Data8`, `Data9`, `Data10`, `Data11`, `Data12`, `Data13`, `Data14`, `Data15`, `Data16`, `Data17`, `Data18`, `Data19`, `Data20`, `Data21`, `Data22`, `Data23`, `Data24`, `Data25`, `Data26`, `Data27`, `Data28`, `Data29`, `Data30`, `Data31`, `Data32`, `Data33`, `Data34`, `ContentTuningId`, `AIName`, `ScriptName`, `StringId`, `VerifiedBuild`) VALUES 
(204828, 10, 4154, 'Kurzen Cage', '', 'Opening', '', 1.4, 0, 26736, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_kurzen_cage_204828', NULL, 58238);

-- 2. Creature Texts for the event NPCs (Osborn, Emerine, Berrin)
DELETE FROM `creature_text` WHERE `CreatureID` IN (43919, 43920, 43921);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(43919, 0, 0, 'Woo hoo.', 12, 0, 100, 0, 0, 0, 0, 0, 'Osborn Obnoticus'),
(43920, 0, 0, 'Thank you! I don\'t know how much longer we would have survived.', 12, 0, 100, 0, 0, 0, 0, 0, 'Emerine Junis - Text 0'),
(43920, 1, 0, 'That cage was stifling my magic.', 12, 0, 100, 0, 0, 0, 0, 0, 'Emerine Junis - Text 1'),
(43920, 2, 0, 'If you don\'t mind, I\'m going to teleport us back to the Rebel Camp. We\'ll thank you in person later.', 12, 0, 100, 0, 0, 0, 0, 0, 'Emerine Junis - Text 2'),
(43921, 0, 0, 'Freedom! Sweet, sweet freedom!', 12, 0, 100, 0, 0, 0, 0, 0, 'Berrin Burnquill');