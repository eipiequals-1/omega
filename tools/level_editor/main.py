from typing import List
import pygame
import os
import json

WIDTH = 1600
HEIGHT = 900

pygame.init()

window = pygame.display.set_mode([WIDTH, HEIGHT])
pygame.display.set_caption("Omega Level Editor")

clock = pygame.time.Clock()

FONT25 = pygame.font.SysFont("uroob", 25)


WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BG_COLOR = (20, 20, 20)
LINE_COLOR = (120, 120, 120)

text_surfaces = {}
def render_text(surface, text, x, y):
    global text_surfaces
    if text_surfaces.get(text) is not None:
        surface.blit(text_surfaces.get(text), (x, y))
        return

    new_surf = FONT25.render(text, True, WHITE)
    text_surfaces[text] = new_surf
    surface.blit(new_surf, (x, y))

class Tileset:
    def __init__(self, tile_size, filepath):
        self.tile_size = tile_size

        self.filepath = filepath
        self.texture = pygame.image.load(filepath)

        self.cols = self.texture.get_width() // self.tile_size
        self.rows = self.texture.get_height() // self.tile_size
        
        # load empty tiles
        self.tiles = []
        for y in range(self.rows):
            self.tiles.append([])
            for x in range(self.cols):
                tile = {
                    "properties": [],
                }
                self.tiles[y].append(tile)

        self.tiles[0][0]["properties"].append("block")

        # load surfaces
        self.surfaces = []
        for i in range(self.cols * self.rows):
            x = i % self.cols
            y = i // self.cols
            subsurface = self.texture.subsurface((
                x * self.tile_size,
                y * self.tile_size,
                self.tile_size,
                self.tile_size
            ))
            self.surfaces.append(subsurface)
    
    def get_subsurface(self, tile_id) -> pygame.Surface:
        return self.surfaces[tile_id]

    def save_to_file(self, filepath):
        with open(filepath, "w") as f:
            data = {
                    "tileset": self.filepath,
                    "width": self.cols,
                    "height": self.rows,
                    "tile_size": self.tile_size,
                    "tiles": self.tiles
            }
            json.dump(data, f, indent=4)


class Tile:
    def __init__(self, tile_size, tile_id):
        self.tile_size = tile_size
        self.tile_id = tile_id


class Grid:
    def __init__(self, cols, rows, tile_size):
        self.cols = cols
        self.rows = rows
        self.tile_size = tile_size   

        self.tiles = []
        for y in range(self.rows):
            self.tiles.append([])
            for x in range(self.cols):
                # use -1 for no tile
                self.tiles[y].append(Tile(self.tile_size, -1))

        self.surface = pygame.Surface((self.cols * self.tile_size,
                                       self.rows * self.tile_size))
        self.draw_grid()

    def render(self, surface, scroll, zoom):
        # create scaled surface
        scale = pygame.transform.scale(self.surface,
                                       (self.surface.get_width() * zoom,
                                        self.surface.get_height() * zoom))
        surface.blit(scale, (scroll[0], scroll[1]))

        # render the mouse position
        
    def set_tile(self, x, y, tileset : Tileset, tile_id):
        tile = self.tiles[y][x]
        tile.tile_id = tile_id
        if tile_id > -1:
            subsurface = tileset.get_subsurface(tile_id)

            # render the subsurface to the grid surface
            self.surface.blit(subsurface, (x * self.tile_size, y * self.tile_size))
        else:
            # draw a black icon on the block
            pygame.draw.rect(self.surface,
                             BLACK,
                             (x * self.tile_size,
                              y * self.tile_size,
                              self.tile_size,
                              self.tile_size))

        self.draw_grid()

    def draw_grid(self):
        for y in range(self.rows):
            pygame.draw.line(self.surface,
                             LINE_COLOR,
                             (0, y * self.tile_size),
                             (self.cols * self.tile_size, y * self.tile_size),
                             1)
        for x in range(self.cols):
            pygame.draw.line(self.surface,
                             LINE_COLOR,
                             (x * self.tile_size, 0),
                             (x * self.tile_size, self.rows * self.tile_size),
                             1)


class UIBuffer:
    def __init__(self, x, y, width, height, tileset):
        self.rect = pygame.Rect(x, y, width, height)
        self.surface = pygame.Surface((width, height))
        self.tileset : Tileset = tileset

        self.selected_index = 0
        self.tileset_render_rect = pygame.Rect(10,
                                               45,
                                               self.rect.width,
                                               self.rect.width)

        self.background_color = (20, 34, 43)

    def render(self, surface, scroll, zoom):
        pygame.draw.rect(self.surface,
                         self.background_color,
                         (0, 0, self.rect.width, self.rect.height))


        # draw tileset as buttons
        new_surface = pygame.transform.scale(self.tileset.texture, (
            self.tileset.texture.get_width() * zoom,
            self.tileset.texture.get_height() * zoom))
        self.surface.blit(new_surface, (
            self.tileset_render_rect.x + scroll[0],
            self.tileset_render_rect.y + scroll[1]
        ))

        # draw border around tileset
        border = 2
        pygame.draw.rect(self.surface, (128, 128, 128), (
            self.tileset_render_rect.x + scroll[0] - border,
            self.tileset_render_rect.y + scroll[1] - border,
            new_surface.get_width() + border * 2,
            new_surface.get_height() + border * 2
        ), border)

        # draw selected rectangle
        selected_x = self.selected_index % self.tileset.cols
        selected_y = self.selected_index // self.tileset.cols
        render_x = (self.tileset_render_rect.x + scroll[0] +
                    selected_x * self.tileset.tile_size * zoom)
        render_y = (self.tileset_render_rect.y + scroll[1] +
                    selected_y * self.tileset.tile_size * zoom)

        pygame.draw.rect(
            self.surface,
            (200, 10, 0),
            (render_x, render_y,
             self.tileset.tile_size * zoom, self.tileset.tile_size * zoom),
            round(zoom))

        # hide the buttom of the tileset
        pygame.draw.rect(self.surface,
                         self.background_color,
                         (0,
                          self.tileset_render_rect.bottom,
                          self.rect.width,
                          self.rect.height - self.tileset_render_rect.height))


        # draw the tileset name
        tileset_name_surface = FONT25.render(
            self.tileset.filepath,
            True,
            WHITE)
        self.surface.blit(tileset_name_surface, (10, 10))

        pygame.draw.line(self.surface,
                         (40, 54, 63),
                         (0, 0),
                         (0, self.rect.height),
                         2)

        property_surf = FONT25.render("Properties:", True, WHITE)
        self.surface.blit(property_surf,
                          (10, self.tileset_render_rect.bottom + 10))
        
        # draw the properties
        tile_data = self.tileset.tiles[selected_y][selected_x]
        for i, property in enumerate(tile_data["properties"]):
            property_surf = FONT25.render(">  '" + property + "'", True, WHITE)
            self.surface.blit(property_surf, (10, self.tileset_render_rect.bottom + 40 + 30 * i))

        # draw the surface to the screen
        surface.blit(self.surface, self.rect)

    """
    Render the tileset panel in the given rectangle
    Return the maximum y it attained
    """
    def tileset_panel(self, rect) -> float:
        pass

    def handle_input(self, mx, my, zoom, scroll):
        # check if the user is clicking on the tileset
        tileset_rect = pygame.Rect(
            self.rect.x + self.tileset_render_rect.x + scroll[0],
            self.rect.y + self.tileset_render_rect.y + scroll[1],
            self.tileset.texture.get_width() * zoom,
            self.tileset.texture.get_height() * zoom
        )
        if tileset_rect.collidepoint(mx, my) and self.rect.collidepoint(mx, my):
            x = int((mx - tileset_rect.x) / 
                     zoom // self.tileset.tile_size)
            y = int((my - tileset_rect.y) / 
                     zoom // self.tileset.tile_size)
            self.selected_index = y * self.tileset.cols + x


def main():
    run = True
    scroll: List[float] = [0, 0]
    tileset_scroll: List[float] = [0, 0]

    tile_size = 16

    grid = Grid(50, 35, tile_size)
    tileset = Tileset(tile_size, "./res/tileset.png")
    ui_buffer = UIBuffer(WIDTH * 0.75, 0, WIDTH * 0.25, HEIGHT, tileset)

    scroll_speed = 10

    grid_zoom = 1
    tileset_zoom = 1

    while run:

        keys = pygame.key.get_pressed()
        mx, my = pygame.mouse.get_pos()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

            elif event.type == pygame.MOUSEWHEEL:
                # check if it is over the ui buffer or the grid
                if ui_buffer.rect.collidepoint(mx, my):
                    tileset_zoom += event.y * 0.5
                    if tileset_zoom < 0:
                        tileset_zoom = 0
                # over grid
                else:
                    # positive event.y -> zoom in
                    # negative event.y -> zoom out
                    grid_zoom += event.y * 0.5
                    if grid_zoom < 0:
                        grid_zoom = 0


        moused_pressed = pygame.mouse.get_pressed()
        # left click
        if moused_pressed[0]:
            if ui_buffer.rect.collidepoint(mx, my):
                ui_buffer.handle_input(mx, my, tileset_zoom, tileset_scroll)
            else:
                tile_x = int((mx - scroll[0]) / grid_zoom // tile_size)
                tile_y = int((my - scroll[1]) / grid_zoom // tile_size)
                # check if it is not out of range
                # or if it does not collide with the UI Buffer
                if 0 <= tile_x < grid.cols and 0 <= tile_y < grid.rows:
                    grid.set_tile(
                        tile_x, tile_y,tileset, ui_buffer.selected_index)

        elif moused_pressed[2]:
            if ui_buffer.rect.collidepoint(mx, my):
                pass
            else:
                tile_x = int((mx - scroll[0]) / grid_zoom // tile_size)
                tile_y = int((my - scroll[1]) / grid_zoom // tile_size)
                # check if it is not out of range
                # or if it does not collide with the UI Buffer
                if 0 <= tile_x < grid.cols and 0 <= tile_y < grid.rows:
                    grid.set_tile(tile_x, tile_y, tileset, -1)
           
 
        if keys[pygame.K_ESCAPE]:
            run = False

        # handle movement of grid
        if keys[pygame.K_LEFT] or keys[pygame.K_a]:
            if ui_buffer.rect.collidepoint(mx, my):
                tileset_scroll[0] += scroll_speed * tileset_zoom
            else:
                scroll[0] += scroll_speed * grid_zoom

        if keys[pygame.K_RIGHT] or keys[pygame.K_d]:
            if ui_buffer.rect.collidepoint(mx, my):
                tileset_scroll[0] -= scroll_speed * tileset_zoom
            else:
                scroll[0] -= scroll_speed * grid_zoom

        if keys[pygame.K_UP] or keys[pygame.K_w]:
            if ui_buffer.rect.collidepoint(mx, my):
                tileset_scroll[1] += scroll_speed * tileset_zoom
            else:
                scroll[1] += scroll_speed * grid_zoom

        if keys[pygame.K_DOWN] or keys[pygame.K_s]:
            if ui_buffer.rect.collidepoint(mx, my):
                tileset_scroll[1] -= scroll_speed * tileset_zoom
            else:
                scroll[1] -= scroll_speed * grid_zoom

        # handle zooming on using ctrl +/-
        if keys[pygame.K_LCTRL] or keys[pygame.K_RCTRL]:
            if keys[pygame.K_EQUALS]:
                grid_zoom += 0.5
                print(True)
            elif keys[pygame.K_MINUS]:
                grid_zoom -= 0.5
            if grid_zoom < 0:
                grid_zoom = 0

        # rendering
        window.fill((BG_COLOR))

        grid.render(window, scroll, grid_zoom)
        ui_buffer.render(window, tileset_scroll, tileset_zoom)

        pygame.display.update()
        clock.tick(30)

    tileset.save_to_file("./res/tileset.json")
    pygame.quit()

if __name__ == "__main__":
    main()
