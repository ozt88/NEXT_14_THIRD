-- MySQL Script generated by MySQL Workbench
-- 11/13/14 21:56:37
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Stage`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Stage` (
  `StageID` INT NOT NULL,
  `sLevel` INT NOT NULL DEFAULT 0,
  `sWidth` INT NOT NULL DEFAULT 0,
  `sHeight` INT NOT NULL DEFAULT 0,
  `sRoomNum` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`StageID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Room`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Room` (
  `roomID` INT NOT NULL AUTO_INCREMENT,
  `rWidth` INT NOT NULL DEFAULT 0,
  `rHeight` INT NOT NULL DEFAULT 0,
  `rPosX` INT NOT NULL DEFAULT 0,
  `rPosY` INT NOT NULL DEFAULT 0,
  `Stage_StageID` INT NOT NULL,
  PRIMARY KEY (`roomID`, `Stage_StageID`),
  INDEX `fk_Room_Stage1_idx` (`Stage_StageID` ASC),
  CONSTRAINT `fk_Room_Stage1`
    FOREIGN KEY (`Stage_StageID`)
    REFERENCES `mydb`.`Stage` (`StageID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Player`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Player` (
  `playerID` INT NOT NULL AUTO_INCREMENT,
  `pMaxHp` INT NOT NULL DEFAULT 0,
  `pMaxSteam` INT NOT NULL DEFAULT 0,
  `pHp` INT NOT NULL DEFAULT 0,
  `pSteam` INT NOT NULL DEFAULT 0,
  `pDirection` INT NOT NULL DEFAULT 0,
  `pSpeed` INT NOT NULL DEFAULT 0,
  `pAttack` INT NOT NULL DEFAULT 0,
  `pDepense` INT NOT NULL DEFAULT 0,
  `pPosX` INT NOT NULL DEFAULT 0,
  `pPosY` INT NOT NULL DEFAULT 0,
  `pVelocityX` INT NOT NULL DEFAULT 0,
  `pVelocityY` INT NOT NULL DEFAULT 0,
  `pLevel` INT NOT NULL DEFAULT 0,
  `pGear` INT(4) NOT NULL DEFAULT 0,
  `pExp` INT NOT NULL DEFAULT 0,
  `pAttackSpeed` INT NOT NULL DEFAULT 0,
  `pName` VARCHAR(45) NOT NULL DEFAULT 0,
  `Room_roomID` INT NOT NULL,
  `Room_Stage_StageID` INT NOT NULL,
  PRIMARY KEY (`playerID`),
  INDEX `fk_Player_Room1_idx` (`Room_roomID` ASC, `Room_Stage_StageID` ASC),
  CONSTRAINT `fk_Player_Room1`
    FOREIGN KEY (`Room_roomID` , `Room_Stage_StageID`)
    REFERENCES `mydb`.`Room` (`roomID` , `Stage_StageID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Monster`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Monster` (
  `monsterID` INT NOT NULL AUTO_INCREMENT,
  `mName` VARCHAR(45) NOT NULL,
  `mLevel` INT NOT NULL,
  `mMaxHp` INT NOT NULL,
  `mMaxMp` INT NOT NULL,
  `mHp` INT NOT NULL,
  `mMp` INT NOT NULL,
  `mAttack` INT NOT NULL,
  `mDepense` INT NOT NULL,
  `mPosX` INT NOT NULL,
  `mPosY` INT NOT NULL,
  `mVelocityX` INT NOT NULL,
  `mVelocityY` INT NOT NULL,
  `Room_roomID` INT NOT NULL,
  `Room_Stage_StageID` INT NOT NULL,
  PRIMARY KEY (`monsterID`),
  INDEX `fk_Monster_Room1_idx` (`Room_roomID` ASC, `Room_Stage_StageID` ASC),
  CONSTRAINT `fk_Monster_Room1`
    FOREIGN KEY (`Room_roomID` , `Room_Stage_StageID`)
    REFERENCES `mydb`.`Room` (`roomID` , `Stage_StageID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`State`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`State` (
  `stateID` INT NOT NULL AUTO_INCREMENT,
  `stateName` VARCHAR(45) NOT NULL DEFAULT 0,
  `Player_playerID` INT NOT NULL,
  `Monster_monsterID` INT NOT NULL,
  PRIMARY KEY (`stateID`),
  INDEX `fk_State_Player1_idx` (`Player_playerID` ASC),
  INDEX `fk_State_Monster1_idx` (`Monster_monsterID` ASC),
  CONSTRAINT `fk_State_Player1`
    FOREIGN KEY (`Player_playerID`)
    REFERENCES `mydb`.`Player` (`playerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_State_Monster1`
    FOREIGN KEY (`Monster_monsterID`)
    REFERENCES `mydb`.`Monster` (`monsterID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Inventory`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Inventory` (
  `invenID` INT NOT NULL AUTO_INCREMENT,
  `capacity` INT NOT NULL DEFAULT 0,
  `Player_playerID` INT NOT NULL,
  PRIMARY KEY (`invenID`, `Player_playerID`),
  INDEX `fk_Inventory_Player1_idx` (`Player_playerID` ASC),
  CONSTRAINT `fk_Inventory_Player1`
    FOREIGN KEY (`Player_playerID`)
    REFERENCES `mydb`.`Player` (`playerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Item`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Item` (
  `itemID` INT NOT NULL DEFAULT 0,
  `iWeight` INT NOT NULL DEFAULT 0,
  `iWidth` INT NOT NULL DEFAULT 0,
  `iHeight` INT NOT NULL DEFAULT 0,
  `iType` INT NOT NULL DEFAULT 0,
  `iPrice` INT NOT NULL DEFAULT 0,
  `iIsAvailable` TINYINT(1) NOT NULL DEFAULT 0,
  `iEnergyCost` INT NOT NULL DEFAULT 0,
  `iName` VARCHAR(45) NOT NULL DEFAULT 0,
  PRIMARY KEY (`itemID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Inventory_has_Item`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Inventory_has_Item` (
  `Inventory_invenID` INT NOT NULL,
  `Inventory_Player_playerID` INT NOT NULL,
  `Item_itemID` INT NULL,
  PRIMARY KEY (`Inventory_invenID`, `Inventory_Player_playerID`, `Item_itemID`),
  INDEX `fk_Inventory_has_Item_Item1_idx` (`Item_itemID` ASC),
  INDEX `fk_Inventory_has_Item_Inventory1_idx` (`Inventory_invenID` ASC, `Inventory_Player_playerID` ASC),
  CONSTRAINT `fk_Inventory_has_Item_Inventory1`
    FOREIGN KEY (`Inventory_invenID` , `Inventory_Player_playerID`)
    REFERENCES `mydb`.`Inventory` (`invenID` , `Player_playerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Inventory_has_Item_Item1`
    FOREIGN KEY (`Item_itemID`)
    REFERENCES `mydb`.`Item` (`itemID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`stat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`stat` (
  `statType` INT NOT NULL AUTO_INCREMENT,
  `statQuantity` INT NOT NULL DEFAULT 0,
  `Item_itemID` INT NOT NULL,
  PRIMARY KEY (`statType`, `Item_itemID`),
  INDEX `fk_stat_Item1_idx` (`Item_itemID` ASC),
  CONSTRAINT `fk_stat_Item1`
    FOREIGN KEY (`Item_itemID`)
    REFERENCES `mydb`.`Item` (`itemID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`effect`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`effect` (
  `effectID` INT NOT NULL AUTO_INCREMENT,
  `description` VARCHAR(100) NULL,
  `Item_itemID` INT NOT NULL,
  PRIMARY KEY (`effectID`, `Item_itemID`),
  INDEX `fk_effect_Item1_idx` (`Item_itemID` ASC),
  CONSTRAINT `fk_effect_Item1`
    FOREIGN KEY (`Item_itemID`)
    REFERENCES `mydb`.`Item` (`itemID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`AI`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`AI` (
  `AIType` INT NOT NULL AUTO_INCREMENT,
  `Monster_monsterID` INT NOT NULL,
  PRIMARY KEY (`AIType`, `Monster_monsterID`),
  INDEX `fk_AI_Monster1_idx` (`Monster_monsterID` ASC),
  CONSTRAINT `fk_AI_Monster1`
    FOREIGN KEY (`Monster_monsterID`)
    REFERENCES `mydb`.`Monster` (`monsterID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Module`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Module` (
  `ModuleID` INT NOT NULL AUTO_INCREMENT,
  `mWidth` INT NOT NULL DEFAULT 0,
  `mHeight` INT NOT NULL DEFAULT 0,
  `ModuleType` INT NOT NULL,
  PRIMARY KEY (`ModuleID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Tile`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Tile` (
  `TileID` INT NOT NULL AUTO_INCREMENT,
  `tWidth` INT NOT NULL DEFAULT 0,
  `tHeight` INT NOT NULL DEFAULT 0,
  `tAttack` INT NULL,
  `tCoolTime` INT NULL,
  PRIMARY KEY (`TileID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Item_has_Monster`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Item_has_Monster` (
  `Item_itemID` INT NULL,
  `Monster_monsterID` INT NULL,
  `DropChance` DECIMAL(0,2) NOT NULL DEFAULT 0.00,
  PRIMARY KEY (`Item_itemID`, `Monster_monsterID`),
  INDEX `fk_Item_has_Monster_Monster1_idx` (`Monster_monsterID` ASC),
  INDEX `fk_Item_has_Monster_Item1_idx` (`Item_itemID` ASC),
  CONSTRAINT `fk_Item_has_Monster_Item1`
    FOREIGN KEY (`Item_itemID`)
    REFERENCES `mydb`.`Item` (`itemID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Item_has_Monster_Monster1`
    FOREIGN KEY (`Monster_monsterID`)
    REFERENCES `mydb`.`Monster` (`monsterID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Room_has_Module`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Room_has_Module` (
  `Room_roomID` INT NOT NULL,
  `Room_Stage_StageID` INT NOT NULL,
  `Module_ModuleID` INT NOT NULL,
  `Module_PosX` INT NOT NULL DEFAULT 0,
  `Module_PosY` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`Room_roomID`, `Room_Stage_StageID`, `Module_ModuleID`),
  INDEX `fk_Room_has_Module_Module1_idx` (`Module_ModuleID` ASC),
  INDEX `fk_Room_has_Module_Room1_idx` (`Room_roomID` ASC, `Room_Stage_StageID` ASC),
  CONSTRAINT `fk_Room_has_Module_Room1`
    FOREIGN KEY (`Room_roomID` , `Room_Stage_StageID`)
    REFERENCES `mydb`.`Room` (`roomID` , `Stage_StageID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Room_has_Module_Module1`
    FOREIGN KEY (`Module_ModuleID`)
    REFERENCES `mydb`.`Module` (`ModuleID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Module_has_Tile`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Module_has_Tile` (
  `Module_ModuleID` INT NOT NULL,
  `Tile_TileID` INT NOT NULL,
  `tile_PosX` INT NOT NULL DEFAULT 0,
  `tile_PosY` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`Module_ModuleID`, `Tile_TileID`),
  INDEX `fk_Module_has_Tile_Tile1_idx` (`Tile_TileID` ASC),
  INDEX `fk_Module_has_Tile_Module1_idx` (`Module_ModuleID` ASC),
  CONSTRAINT `fk_Module_has_Tile_Module1`
    FOREIGN KEY (`Module_ModuleID`)
    REFERENCES `mydb`.`Module` (`ModuleID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Module_has_Tile_Tile1`
    FOREIGN KEY (`Tile_TileID`)
    REFERENCES `mydb`.`Tile` (`TileID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Animation`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Animation` (
  `AnimationID` INT NOT NULL AUTO_INCREMENT,
  `AnimationDelay` INT NULL,
  `AnimationPath` VARCHAR(100) NOT NULL,
  `AnimationFrameCount` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`AnimationID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Sprite`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Sprite` (
  `SpriteID` INT NOT NULL AUTO_INCREMENT,
  `spritePath` VARCHAR(100) NOT NULL,
  `spriteWidth` INT NOT NULL DEFAULT 0,
  `spriteHeight` INT NOT NULL DEFAULT 0,
  `Animation_AnimationID` INT NULL DEFAULT 0,
  `Player_playerID` INT NOT NULL,
  `Tile_TileID` INT NULL,
  `spritePosX` INT NOT NULL DEFAULT 0,
  `spritePosY` INT NOT NULL DEFAULT 0,
  `isVisible` TINYINT(1) NOT NULL DEFAULT 0,
  `scale` INT NOT NULL DEFAULT 0,
  `rotate` INT NOT NULL DEFAULT 0,
  `Monster_monsterID` INT NOT NULL,
  PRIMARY KEY (`SpriteID`),
  INDEX `fk_Sprite_Animation1_idx` (`Animation_AnimationID` ASC),
  INDEX `fk_Sprite_Player1_idx` (`Player_playerID` ASC),
  INDEX `fk_Sprite_Tile1_idx` (`Tile_TileID` ASC),
  INDEX `fk_Sprite_Monster1_idx` (`Monster_monsterID` ASC),
  CONSTRAINT `fk_Sprite_Animation1`
    FOREIGN KEY (`Animation_AnimationID`)
    REFERENCES `mydb`.`Animation` (`AnimationID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Sprite_Player1`
    FOREIGN KEY (`Player_playerID`)
    REFERENCES `mydb`.`Player` (`playerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Sprite_Tile1`
    FOREIGN KEY (`Tile_TileID`)
    REFERENCES `mydb`.`Tile` (`TileID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Sprite_Monster1`
    FOREIGN KEY (`Monster_monsterID`)
    REFERENCES `mydb`.`Monster` (`monsterID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
