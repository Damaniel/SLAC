import sys, json, re
from PySide6.QtWidgets import QApplication, QMainWindow, QFileDialog, QListWidgetItem, QGraphicsScene
from PySide6.QtCore import QFile, Slot, QRect
from PySide6.QtGui import QImage, QPixmap, QPainter
from enemyeditor import Ui_EnemyEditor

class Hero:
    def __init__(self):
        self.hp = 100
        self.max_hp = 100
        self.action_points = 0
        self.str = 10
        self.dex = 10
        self.con = 10
        self.defense = 10
        self.atk = 10
        self.spd = 100
        self.f_atk = 0
        self.i_atk = 0
        self.l_atk = 0
        self.f_def = 0
        self.i_def = 0
        self.l_def = 0
        self.f_dmg = 0
        self.i_dmg = 0
        self.l_dmg = 0
        self.block = 0
        self.apt = 1

    def get_stats(self):
        stats = {}
        stats['hp'] = self.hp
        stats['max_hp'] = self.max_hp
        stats['str'] = self.str
        stats['dex'] = self.dex
        stats['con'] = self.con
        stats['def'] = self.defense
        stats['atk'] = self.atk
        stats['spd'] = self.spd
        stats['f_atk'] = self.f_atk
        stats['i_atk'] = self.i_atk
        stats['l_atk'] = self.l_atk
        stats['f_def'] = self.f_def
        stats['i_def'] = self.i_def
        stats['l_def'] = self.l_def
        stats['f_dmg'] = self.f_dmg
        stats['i_dmg'] = self.i_dmg
        stats['l_dmg'] = self.l_dmg
        stats['block'] = self.block
        stats['apt'] = self.apt
        return stats

    def set_stats(self, stats):
        self.hp = stats['hp']
        self.max_hp = stats['max_hp']
        self.str = stats['str']
        self.dex = stats['dex']
        self.con = stats['con']
        self.defense = stats['def']
        self.atk = stats['atk']
        self.spd = stats['spd']
        self.f_atk = stats['f_atk']
        self.i_atk = stats['i_atk']
        self.l_atk = stats['l_atk']
        self.f_def = stats['f_def']
        self.i_def = stats['i_def']
        self.l_def = stats['l_def']
        self.f_dmg = stats['f_dmg']
        self.i_dmg = stats['i_dmg']
        self.l_dmg = stats['l_dmg']
        self.block = stats['block']
        self.apt = stats['apt']

    def reset_health(self):
        self.hp = self.max_hp

    # Takes the target to attack.
    # Returns a string that will be placed into the combat log
    def attack(self, target):
        output = "Player attacks!"
        return output

class Mob:
    def __init__(self):
        self.hp = 0
        self.max_hp = 0
        self.action_points = 0
        self.str = 0
        self.defense = 0
        self.atk = 0
        self.spd = 0
        self.f_atk = 0
        self.i_atk = 0
        self.l_atk = 0
        self.f_def = 0
        self.i_def = 0
        self.l_def = 0
        self.apt = 0

    def get_stats(self):
        stats = {}
        stats['hp'] = self.hp
        stats['max_hp'] = self.max_hp
        stats['str'] = self.str
        stats['def'] = self.defense
        stats['atk'] = self.atk
        stats['spd'] = self.spd
        stats['f_atk'] = self.f_atk
        stats['i_atk'] = self.i_atk
        stats['l_atk'] = self.l_atk
        stats['f_def'] = self.f_def
        stats['i_def'] = self.i_def
        stats['l_def'] = self.l_def
        stats['apt'] = self.apt
        return stats

    def set_stats(self, stats):
        self.hp = stats['hp']
        self.max_hp = stats['max_hp']
        self.str = stats['str']
        self.defense = stats['def']
        self.atk = stats['atk']
        self.spd = stats['spd']
        self.f_atk = stats['f_atk']
        self.i_atk = stats['i_atk']
        self.l_atk = stats['l_atk']
        self.f_def = stats['f_def']
        self.i_def = stats['i_def']
        self.l_def = stats['l_def']
        self.apt = stats['apt']

    def reset_health(self):
        self.hp = self.max_hp

    def attack(self, target):
        output = "Enemy attacks!"
        return output

class MainWindow(QMainWindow):
    def __init__(self):
        self.enemy_json = {}
        self.active_file = None
        self.combat_enabled = False
        self.blank_id_idx = 0
        self.enemy_pixmap = QPixmap('enemies.png')
        self.player = Hero()
        self.enemy = Mob()

        # Set up the visual part of the UI
        super(MainWindow, self).__init__()
        self.ui = Ui_EnemyEditor()
        self.ui.setupUi(self)

        #
        # Open an empty version of the JSON file with all metadata headers present.
        # (that way, a 'new' file will get the headers too)
        self.load_enemy_json_file('skel.json')
        
        # initialize the player fields 
        fields = self.player.get_stats()
        self.populate_player_fields(fields)

        # Set the attack button to disabled initially
        self.ui.PlayerAttack.setEnabled(False)

        # Connect all of the signals and slots together
        self.ui.EnemyAddButton.clicked.connect(self.add_enemy_button_action)
        self.ui.EnemyDeleteButton.clicked.connect(self.delete_enemy_button_action)
        self.ui.LoadFile.clicked.connect(self.load_file_button_action)
        self.ui.SaveFile.clicked.connect(self.save_file_button_action)
        self.ui.Exit.clicked.connect(self.exit_program)
        self.ui.ResetBattle.clicked.connect(self.reset_battle)
        self.ui.PlayerAttack.clicked.connect(self.attack_round)
        # Connect both clicking on an item and scrolling down the list to the update function
        self.ui.EnemiesList.itemClicked.connect(self.update_enemy_data)
        self.ui.EnemiesList.currentRowChanged.connect(self.update_enemy_data)
        self.ui.SimEnemiesList.itemClicked.connect(self.update_enemy_stats)
        self.ui.SimEnemiesList.currentRowChanged.connect(self.update_enemy_stats)
        self.ui.tabWidget.tabBarClicked.connect(self.click_tab_function)
        self.ui.EnemyKeyVal.editingFinished.connect(self.update_active_enemy_key)
        self.ui.EnemyIDVal.editingFinished.connect(self.update_active_enemy_id)
        self.ui.EnemyNameVal.editingFinished.connect(self.update_active_enemy_name)
        self.ui.EnemyBIDVal.editingFinished.connect(self.update_active_enemy_bid)
        self.ui.EnemyGIDVal.editingFinished.connect(self.update_active_enemy_gid)
        self.ui.EnemyHPVal.editingFinished.connect(self.update_active_enemy_hp)
        self.ui.EnemySTRVal.editingFinished.connect(self.update_active_enemy_str)
        self.ui.EnemySPDVal.editingFinished.connect(self.update_active_enemy_spd)
        self.ui.EnemyATKVal.editingFinished.connect(self.update_active_enemy_atk)
        self.ui.EnemyDEFVal.editingFinished.connect(self.update_active_enemy_def)
        self.ui.EnemyAPTVal.editingFinished.connect(self.update_active_enemy_apt)
        self.ui.EnemyFATKVal.editingFinished.connect(self.update_active_enemy_fatk)
        self.ui.EnemyFDEFVal.editingFinished.connect(self.update_active_enemy_fdef)
        self.ui.EnemyIATKVal.editingFinished.connect(self.update_active_enemy_iatk)
        self.ui.EnemyIDEFVal.editingFinished.connect(self.update_active_enemy_idef)
        self.ui.EnemyLATKVal.editingFinished.connect(self.update_active_enemy_latk)
        self.ui.EnemyLDEFVal.editingFinished.connect(self.update_active_enemy_ldef)
        self.ui.PlayerHPVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerMaxHPVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerSTRVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerCONVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerDEXVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerATKVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerDEFVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerSPDVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerFATKVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerIATKVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerLATKVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerFDEFVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerIDEFVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerLDEFVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerFDMGVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerIDMGVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerLDMGVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerBlockVal.editingFinished.connect(self.update_player_stats)
        self.ui.PlayerAPTVal.editingFinished.connect(self.update_player_stats)
        self.ui.EnemyExpVal.editingFinished.connect(self.update_active_enemy_exp)
        self.ui.EnemyLevelVal.editingFinished.connect(self.update_active_enemy_elevel)
        self.ui.EnemyILevelVal.editingFinished.connect(self.update_active_enemy_ilevel)
        self.ui.EnemyRarityVal.editingFinished.connect(self.update_active_enemy_rarity)
        self.ui.EnemyMaxItemsVal.editingFinished.connect(self.update_active_enemy_max_items)

    # Loads an enemy JSON file
    def load_enemy_json_file(self, filename):
        f = open(filename, 'r')
        self.enemy_json = json.load(f)
        f.close()

    # Saves an enemy JSON file
    def save_enemy_json_file(self, filename):
        f = open(filename, 'w')
        json.dump(self.enemy_json, f, indent=4)
        f.close()

    def create_new_enemy(self):
        enemy_key = 'new_enemy_' + str(self.blank_id_idx)
        self.blank_id_idx +=1
        self.enemy_json['enemy']['items'][enemy_key] = {}
        self.enemy_json['enemy']['items'][enemy_key]['id'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['name'] = "New Enemy"
        self.enemy_json['enemy']['items'][enemy_key]['bid'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['gid'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['hp'] = 10
        self.enemy_json['enemy']['items'][enemy_key]['str'] = 10
        self.enemy_json['enemy']['items'][enemy_key]['spd'] = 50
        self.enemy_json['enemy']['items'][enemy_key]['atk'] = 10
        self.enemy_json['enemy']['items'][enemy_key]['def'] = 10
        self.enemy_json['enemy']['items'][enemy_key]['apt'] = 1
        self.enemy_json['enemy']['items'][enemy_key]['f_atk'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['i_atk'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['l_atk'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['f_def'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['i_def'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['l_def'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['exp'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['elevel'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['ilevel'] = 0
        self.enemy_json['enemy']['items'][enemy_key]['rarity'] = 255
        self.enemy_json['enemy']['items'][enemy_key]['max_items'] = 1
        # Add the item to the scrollable list and make it the active item
        self.ui.EnemiesList.addItem(enemy_key)
        self.ui.EnemiesList.setCurrentRow(self.ui.EnemiesList.count() - 1)
        self.populate_enemy_fields()
        self.update_enemy_bitmap()

    def delete_selected_enemy(self):
        # Delete the active item
        enemy_key = self.ui.EnemiesList.currentItem().text()
        self.ui.EnemiesList.takeItem(self.ui.EnemiesList.currentRow())

        # Remove the portion of the JSON file corresponding to it
        del self.enemy_json['enemy']['items'][enemy_key]

        # If there are more than zero items left, make the first item
        # the active item and update the screen
        if self.ui.EnemiesList.count() > 0:
            self.ui.EnemiesList.setCurrentRow(0)
            self.populate_enemy_fields()

    def populate_enemy_fields(self):
        enemy_name = self.ui.EnemiesList.currentItem().text()
        json_data = self.get_single_enemy_data(enemy_name)
        self.ui.EnemyKeyVal.setText(enemy_name)
        self.ui.EnemyIDVal.setText(str(json_data['id']))
        self.ui.EnemyNameVal.setText(json_data['name'])
        self.ui.EnemyBIDVal.setText(str(json_data['bid']))
        self.ui.EnemyGIDVal.setText(str(json_data['gid']))
        self.ui.EnemyHPVal.setText(str(json_data['hp']))
        self.ui.EnemySTRVal.setText(str(json_data['str']))
        self.ui.EnemySPDVal.setText(str(json_data['spd']))
        self.ui.EnemyATKVal.setText(str(json_data['atk']))
        self.ui.EnemyDEFVal.setText(str(json_data['def']))
        self.ui.EnemyAPTVal.setText(str(json_data['apt']))
        self.ui.EnemyFATKVal.setText(str(json_data['f_atk']))
        self.ui.EnemyIATKVal.setText(str(json_data['i_atk']))
        self.ui.EnemyLATKVal.setText(str(json_data['l_atk']))
        self.ui.EnemyFDEFVal.setText(str(json_data['f_def']))
        self.ui.EnemyIDEFVal.setText(str(json_data['i_def']))
        self.ui.EnemyLDEFVal.setText(str(json_data['l_def']))
        self.ui.EnemyExpVal.setText(str(json_data['exp']))
        self.ui.EnemyLevelVal.setText(str(json_data['elevel']))
        self.ui.EnemyILevelVal.setText(str(json_data['ilevel']))
        self.ui.EnemyRarityVal.setText(str(json_data['rarity']))
        self.ui.EnemyMaxItemsVal.setText(str(json_data['max_items']))

    def update_enemy_bitmap(self):
        enemy = self.get_single_enemy_data(self.ui.EnemiesList.currentItem().text())
        temp_enemy_pixmap = QPixmap(64, 64)
        index = enemy['gid']
        x_off = int(int(index) % 32)
        y_off = int(int(index) / 32)
        source_rect = QRect(x_off * 64, y_off * 64, 64, 64)
        dest_rect = QRect(0, 0, 64, 64)
        painter = QPainter(temp_enemy_pixmap)
        painter.drawPixmap(dest_rect, self.enemy_pixmap, source_rect)
        painter.end()
        self.ui.EnemyBitmap.setPixmap(temp_enemy_pixmap)

    # Gets the JSON entry for a single enemy based on its name
    def get_single_enemy_data(self, name):
        return self.enemy_json['enemy']['items'][name]

    def populate_player_fields(self, fields):
        self.ui.PlayerHPVal.setText(str(fields['hp']))
        self.ui.PlayerMaxHPVal.setText(str(fields['max_hp']))
        self.ui.PlayerSTRVal.setText(str(fields['str']))
        self.ui.PlayerCONVal.setText(str(fields['con']))
        self.ui.PlayerDEXVal.setText(str(fields['dex']))
        self.ui.PlayerATKVal.setText(str(fields['atk']))
        self.ui.PlayerDEFVal.setText(str(fields['def']))
        self.ui.PlayerSPDVal.setText(str(fields['spd']))
        self.ui.PlayerFATKVal.setText(str(fields['f_atk']))
        self.ui.PlayerIATKVal.setText(str(fields['i_atk']))
        self.ui.PlayerLATKVal.setText(str(fields['l_atk']))
        self.ui.PlayerFDEFVal.setText(str(fields['f_def']))
        self.ui.PlayerIDEFVal.setText(str(fields['i_def']))
        self.ui.PlayerLDEFVal.setText(str(fields['l_def']))
        self.ui.PlayerFDMGVal.setText(str(fields['f_dmg']))
        self.ui.PlayerIDMGVal.setText(str(fields['i_dmg']))
        self.ui.PlayerLDMGVal.setText(str(fields['l_dmg']))
        self.ui.PlayerBlockVal.setText(str(fields['block']))
        self.ui.PlayerAPTVal.setText(str(fields['apt']))

    def process_field(self, field, key, stats):
        try:
            num = int(field.text())
            if num != '':
                stats[key] = num
            else:
                stats[key] = 0
        except ValueError:
            field.setText('')
            stats[key] = 0

    def update_enemy_stats(self):
        stats = {}
        self.process_field(self.ui.EnemyHPVal, 'hp', stats)
        self.process_field(self.ui.EnemyHPVal, 'max_hp', stats)
        self.process_field(self.ui.EnemySTRVal, 'str', stats)
        self.process_field(self.ui.EnemyATKVal, 'atk', stats)
        self.process_field(self.ui.EnemyDEFVal, 'def', stats)
        self.process_field(self.ui.EnemySPDVal, 'spd', stats)
        self.process_field(self.ui.EnemyAPTVal, 'apt', stats)
        self.process_field(self.ui.EnemyFATKVal, 'f_atk', stats)
        self.process_field(self.ui.EnemyIATKVal, 'i_atk', stats)
        self.process_field(self.ui.EnemyLATKVal, 'l_atk', stats)
        self.process_field(self.ui.EnemyFDEFVal, 'f_def', stats)
        self.process_field(self.ui.EnemyIDEFVal, 'i_def', stats)
        self.process_field(self.ui.EnemyLDEFVal, 'l_def', stats)
        self.enemy.set_stats(stats)
        # This also enables the 'Attack' button
        self.ui.PlayerAttack.setEnabled(True)

    @Slot()
    def update_player_stats(self):
        stats = {}
        self.process_field(self.ui.PlayerHPVal, 'hp', stats)
        self.process_field(self.ui.PlayerMaxHPVal, 'max_hp', stats)
        self.process_field(self.ui.PlayerSTRVal, 'str', stats)
        self.process_field(self.ui.PlayerCONVal, 'con', stats)
        self.process_field(self.ui.PlayerDEXVal, 'dex', stats)
        self.process_field(self.ui.PlayerATKVal, 'atk', stats)
        self.process_field(self.ui.PlayerDEFVal, 'def', stats)
        self.process_field(self.ui.PlayerSPDVal, 'spd', stats)
        self.process_field(self.ui.PlayerFATKVal, 'f_atk', stats)
        self.process_field(self.ui.PlayerIATKVal, 'i_atk', stats)
        self.process_field(self.ui.PlayerLATKVal, 'l_atk', stats)
        self.process_field(self.ui.PlayerFDEFVal, 'f_def', stats)
        self.process_field(self.ui.PlayerIDEFVal, 'i_def', stats)
        self.process_field(self.ui.PlayerLDEFVal, 'l_def', stats)
        self.process_field(self.ui.PlayerFDMGVal, 'f_dmg', stats)
        self.process_field(self.ui.PlayerIDMGVal, 'i_dmg', stats)
        self.process_field(self.ui.PlayerLDMGVal, 'l_dmg', stats)
        self.process_field(self.ui.PlayerBlockVal, 'block', stats)
        self.process_field(self.ui.PlayerAPTVal, 'apt', stats)
        self.player.set_stats(stats)

    @Slot()
    def attack_round(self):
        # Give player and enemy action points equal to speed
        self.ui.CombatLogOutput.appendPlainText("============================================")
        self.player.action_points += self.player.spd
        self.enemy.action_points += self.enemy.spd
        while self.player.action_points >= 100 or self.enemy.action_points >= 100:
            self.ui.CombatLogOutput.appendPlainText(f" - Player now has {self.player.action_points} action points")
            self.ui.CombatLogOutput.appendPlainText(f" - Enemy has {self.enemy.action_points} action points")
            if self.player.action_points >= self.enemy.action_points:
                output = self.player.attack(self.enemy)
                self.ui.CombatLogOutput.appendPlainText(output)
                self.player.action_points -= 100
                self.ui.CombatLogOutput.appendPlainText(f" - Remaining player action points are now {self.player.action_points}")
                if self.enemy.hp <= 0:
                    self.ui.CombatLogOutput.appendPlainText("** Enemy is defeated! **")
                    self.combat_enabled = False
                    self.ui.PlayerAttack.setEnabled(False)

            else:
                output = self.enemy.attack(self.player)
                self.ui.CombatLogOutput.appendPlainText(output)
                self.enemy.action_points -= 100
                self.ui.CombatLogOutput.appendPlainText(f" - Remaining enemy action points are now {self.enemy.action_points}")
                if self.player.hp <= 0:
                    self.ui.CombatLogOutput.appendPlainText("** Player is defeated! **")
                    self.combat_enabled = False
                    self.ui.PlayerAttack.setEnabled(False)
    
    @Slot()
    def reset_battle(self):
        # Set the player's and enemy's stats based
        # on the appropriate boxes
        # Reset health and adjust the value in the box
        self.update_player_stats()
        self.player.reset_health()
        self.update_enemy_stats()
        self.enemy.reset_health()

        # For the player box, set the value of HP to that of Max HP,
        # for visual consistency
        self.ui.PlayerHPVal.setText(str(self.player.hp))

        # Reset all action points
        self.player.action_points = 0
        self.enemy.action_points = 0

        self.ui.CombatLogOutput.appendPlainText("Combat is reset.")
        self.combat_enabled = True
        self.ui.PlayerAttack.setEnabled(True)

    @Slot()
    def update_enemy_data(self):
        self.populate_enemy_fields()
        self.update_enemy_bitmap()

    @Slot()
    def load_file_button_action(self):
        filename = QFileDialog.getOpenFileName(self, caption="Open File", dir="../JSON", filter="JSON files (*.json)")
        self.active_file = filename[0]
        # Load the JSON file
        self.load_enemy_json_file(self.active_file)

        # Clear the existing lists
        self.ui.EnemiesList.clear()
        self.ui.SimEnemiesList.clear()

        # Populate both lists
        for enemy in self.enemy_json['enemy']['items']:
            self.ui.EnemiesList.addItem(enemy)
            self.ui.SimEnemiesList.addItem(enemy)
  
        # If there's items in the list, put the first one's data in the boxes on the right
        if self.ui.EnemiesList.count() > 0:
            self.ui.EnemiesList.setCurrentRow(0)
            self.populate_enemy_fields()
            self.update_enemy_bitmap()

    @Slot()
    def save_file_button_action(self):
        if self.active_file == None or self.active_file == '':
            filename = QFileDialog.getSaveFileName(self, caption="Save File", dir="../JSON", filter="JSON files (*.json);;All files (*)")
            self.active_file = filename[0]
        if self.active_file != None and self.active_file != '':
            self.save_enemy_json_file(self.active_file)

    @Slot()
    def click_tab_function(self, index):
        # If swapping to the sim tab, mirror the editor list to the sim list
        if index == 1:
            self.ui.SimEnemiesList.clear()
            for enemy in self.enemy_json['enemy']['items']:
                self.ui.SimEnemiesList.addItem(enemy)

    @Slot()
    def add_enemy_button_action(self):
        self.create_new_enemy()

    @Slot()
    def delete_enemy_button_action(self):
        self.delete_selected_enemy()

    # Updates the enemy's key value in the JSON file (and the enemy list in the UI)
    @Slot()
    def update_active_enemy_key(self):
        # Get the old name of the key for later work
        old_key_name = self.ui.EnemiesList.currentItem().text()

        # If the name has actually changed, update the JSON file and UI
        # (We have to check for a name change here because this function will delete the portion of the
        # structure keyed under the old name, and things will go wrong if the name hasn't actually
        # changed value)
        if (old_key_name != self.ui.EnemyKeyVal.text()):
            # Replace any spaces with underscores 
            new_key = self.ui.EnemyKeyVal.text()
            new_key = re.sub(' ', '_', new_key)

            # Check to see if this key has the same name as an existing key, if so, don't
            # make the change
            match = False
            for name in self.enemy_json['enemy']['items']:
                if name == new_key:
                    match = True

            if match == True:
                print("Warning: key already exists, no change made!")
                self.ui.EnemyKeyVal.setText(old_key_name)
                return

            self.ui.EnemyKeyVal.setText(new_key)

            # Update the name in the list
            self.ui.EnemiesList.currentItem().setText(new_key)
            # Move the old data to the new key in the JSON structure
            old_data = self.enemy_json['enemy']['items'][old_key_name]
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()] = old_data
            # Delete the data under the old key
            del self.enemy_json['enemy']['items'][old_key_name]

    # Updates the enemy's name in the JSON file
    @Slot()
    def update_active_enemy_name(self):
        if self.ui.EnemyNameVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['name'] = self.ui.EnemyNameVal.text()

    @Slot()
    def update_active_enemy_id(self):
        if self.ui.EnemyIDVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['id'] = self.ui.EnemyIDVal.text()

    @Slot()
    def update_active_enemy_bid(self):
        if self.ui.EnemyBIDVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['bid'] = self.ui.EnemyBIDVal.text()

    @Slot()
    def update_active_enemy_gid(self):
        if self.ui.EnemyGIDVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['gid'] = self.ui.EnemyGIDVal.text()
            self.update_enemy_bitmap()

    @Slot()
    def update_active_enemy_hp(self):
        if self.ui.EnemyHPVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['hp'] = self.ui.EnemyHPVal.text()
    
    @Slot()
    def update_active_enemy_str(self):
        if self.ui.EnemySTRVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['str'] = self.ui.EnemySTRVal.text()

    @Slot()
    def update_active_enemy_spd(self):
        if self.ui.EnemySPDVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['spd'] = self.ui.EnemySPDVal.text()

    @Slot()
    def update_active_enemy_atk(self):
        if self.ui.EnemyATKVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['atk'] = self.ui.EnemyATKVal.text()

    @Slot()
    def update_active_enemy_def(self):
        if self.ui.EnemyDEFVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['def'] = self.ui.EnemyDEFVal.text()

    @Slot()
    def update_active_enemy_apt(self):
        if self.ui.EnemyAPTVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['apt'] = self.ui.EnemyAPTVal.text()

    @Slot()
    def update_active_enemy_fatk(self):
        if self.ui.EnemyFATKVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['f_atk'] = self.ui.EnemyFATKVal.text()

    @Slot()
    def update_active_enemy_iatk(self):
        if self.ui.EnemyIATKVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['i_atk'] = self.ui.EnemyIATKVal.text()

    @Slot()
    def update_active_enemy_latk(self):
        if self.ui.EnemyLATKVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['l_atk'] = self.ui.EnemyLATKVal.text()

    @Slot()
    def update_active_enemy_fdef(self):
        if self.ui.EnemyFDEFVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['f_def'] = self.ui.EnemyFDEFVal.text()

    @Slot()
    def update_active_enemy_idef(self):
        if self.ui.EnemyIDEFVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['i_def'] = self.ui.EnemyIDEFVal.text()

    @Slot()
    def update_active_enemy_ldef(self):
        if self.ui.EnemyLDEFVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['l_def'] = self.ui.EnemyLDEFVal.text()

    @Slot()
    def update_active_enemy_exp(self):
        if self.ui.EnemyExpVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['exp'] = self.ui.EnemyExpVal.text()

    @Slot()
    def update_active_enemy_elevel(self):
        if self.ui.EnemyLevelVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['elevel'] = self.ui.EnemyLevelVal.text()

    @Slot()
    def update_active_enemy_ilevel(self):
        if self.ui.EnemyILevelVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['ilevel'] = self.ui.EnemyILevelVal.text()

    @Slot()
    def update_active_enemy_rarity(self):
        if self.ui.EnemyRarityVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['rarity'] = self.ui.EnemyRarityVal.text()

    @Slot()
    def update_active_enemy_max_items(self):
        if self.ui.EnemyMaxItemsVal.text() != '':
            self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['max_items'] = self.ui.EnemyMaxItemsVal.text()

    @Slot()
    def exit_program(self):
        self.close()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    app.setStyle("windows")
    
    window = MainWindow()
    window.show()
	
    sys.exit(app.exec())