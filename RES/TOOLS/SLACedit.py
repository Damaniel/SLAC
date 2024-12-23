import sys, json, re
from PySide6.QtWidgets import QApplication, QMainWindow, QFileDialog, QListWidgetItem, QGraphicsScene
from PySide6.QtCore import QFile, Slot, QRect
from PySide6.QtGui import QImage, QPixmap, QPainter
from enemyeditor import Ui_EnemyEditor

class MainWindow(QMainWindow):
    def __init__(self):
        self.enemy_json = {}
        self.active_file = None
        self.blank_id_idx = 0
        self.enemy_pixmap = QPixmap('enemies.png')

        # Set up the visual part of the UI
        super(MainWindow, self).__init__()
        self.ui = Ui_EnemyEditor()
        self.ui.setupUi(self)

        #
        # Open an empty version of the JSON file with all metadata headers present.
        # (that way, a 'new' file will get the headers too)
        self.load_enemy_json_file('skel.json')
        
        # Connect all of the signals and slots together
        self.ui.EnemyAddButton.clicked.connect(self.add_enemy_button_action)
        self.ui.EnemyDeleteButton.clicked.connect(self.delete_enemy_button_action)
        self.ui.LoadFile.clicked.connect(self.load_file_button_action)
        self.ui.SaveFile.clicked.connect(self.save_file_button_action)
        self.ui.Exit.clicked.connect(self.exit_program)
        self.ui.EnemiesList.itemClicked.connect(self.update_enemy_data)
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
        x_off = int(int(index) % 64)
        y_off = int(int(index) / 64)
        source_rect = QRect(x_off * 64, y_off * 64, 64, 64)
        dest_rect = QRect(0, 0, 64, 64)
        painter = QPainter(temp_enemy_pixmap)
        painter.drawPixmap(dest_rect, self.enemy_pixmap, source_rect)
        painter.end()
        self.ui.EnemyBitmap.setPixmap(temp_enemy_pixmap)

    # Gets the JSON entry for a single enemy based on its name
    def get_single_enemy_data(self, name):
        return self.enemy_json['enemy']['items'][name]

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
        for enemy in self.enemy_json['enemy']['items']:
            self.ui.EnemiesList.addItem(enemy)
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
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['name'] = self.ui.EnemyNameVal.text()

    @Slot()
    def update_active_enemy_id(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['id'] = self.ui.EnemyIDVal.text()

    @Slot()
    def update_active_enemy_bid(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['bid'] = self.ui.EnemyBIDVal.text()

    @Slot()
    def update_active_enemy_gid(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['gid'] = self.ui.EnemyGIDVal.text()
        self.update_enemy_bitmap()

    @Slot()
    def update_active_enemy_hp(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['hp'] = self.ui.EnemyHPVal.text()
    
    @Slot()
    def update_active_enemy_str(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['str'] = self.ui.EnemySTRVal.text()

    @Slot()
    def update_active_enemy_spd(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['spd'] = self.ui.EnemySPDVal.text()

    @Slot()
    def update_active_enemy_atk(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['atk'] = self.ui.EnemyATKVal.text()

    @Slot()
    def update_active_enemy_def(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['def'] = self.ui.EnemyDEFVal.text()

    @Slot()
    def update_active_enemy_apt(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['apt'] = self.ui.EnemyAPTVal.text()

    @Slot()
    def update_active_enemy_fatk(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['f_atk'] = self.ui.EnemyFATKVal.text()

    @Slot()
    def update_active_enemy_iatk(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['i_atk'] = self.ui.EnemyIATKVal.text()

    @Slot()
    def update_active_enemy_latk(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['l_atk'] = self.ui.EnemyLATKVal.text()

    @Slot()
    def update_active_enemy_fdef(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['f_def'] = self.ui.EnemyFDEFVal.text()

    @Slot()
    def update_active_enemy_idef(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['i_def'] = self.ui.EnemyIDEFVal.text()

    @Slot()
    def update_active_enemy_ldef(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['l_def'] = self.ui.EnemyLDEFVal.text()

    @Slot()
    def update_active_enemy_exp(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['exp'] = self.ui.EnemyExpVal.text()

    @Slot()
    def update_active_enemy_elevel(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['elevel'] = self.ui.EnemyLevelVal.text()

    @Slot()
    def update_active_enemy_ilevel(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['ilevel'] = self.ui.EnemyILevelVal.text()

    @Slot()
    def update_active_enemy_rarity(self):
        self.enemy_json['enemy']['items'][self.ui.EnemiesList.currentItem().text()]['rarity'] = self.ui.EnemyRarityVal.text()

    @Slot()
    def update_active_enemy_max_items(self):
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