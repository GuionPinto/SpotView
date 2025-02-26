import spotipy
from spotipy.oauth2 import SpotifyOAuth
import serial
import time

# Configuración de la autenticación con Spotify
sp = spotipy.Spotify(auth_manager=SpotifyOAuth(client_id="80ab7d3a50e84bb3a9bcaeaad4d77ba1",
                                                client_secret="ebd530a0c2ea4aa9b950ee634f2eb6bf",
                                                redirect_uri="http://localhost:8888/callback",
                                                scope="user-modify-playback-state,user-read-playback-state"))

# Conectar con Arduino
arduino = serial.Serial("COM4", 9600, timeout=1)
time.sleep(2)  # Esperar a que Arduino se inicialice

def get_current_song():
    """Obtiene la canción que se está reproduciendo actualmente en Spotify"""
    track = sp.current_user_playing_track()
    
    if track and track["item"]:  # Verifica si hay una canción reproduciéndose
        artist = track["item"]["artists"][0]["name"]
        t_name = track["item"]["name"]
        song_id = track["item"]["id"]
        duration_ms = float(track["item"]["duration_ms"])  # Obtener duración en milisegundos
        
        return t_name, artist, song_id, duration_ms
    else:
        return None

# Obtener la canción actual
song, artist, songId, duration_ms = get_current_song()

changeSong = 0  # Cambiar a 0 en lugar de False para ser consistente con Arduino
oldSongId = songId

# Enviar los datos iniciales a Arduino
arduino.write(f"{song}, {artist}, {songId}\n".encode())

while True:
    song, artist, songId, duration_ms = get_current_song()
    if songId != oldSongId:  # Si la canción cambió
        changeSong = 1  # Cambiar a 1 si hay un cambio
        arduino.write(f"{song}, {artist}, {changeSong}\n".encode())  # Enviar a Arduino
        print(f'Canción cambiada: {oldSongId} -> {songId}')
        oldSongId = songId  # Actualizar el ID de la canción

    else:
        changeSong = 0  # Si no hay cambio, sigue siendo 0
        arduino.write(f"{song}, {artist}, {songId}\n".encode())  # Enviar a Arduino

    time.sleep(1)  # Enviar datos cada 1 segundo

        

    

