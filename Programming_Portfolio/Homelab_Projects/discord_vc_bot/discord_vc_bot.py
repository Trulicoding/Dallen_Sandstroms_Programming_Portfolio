import discord
import asyncio
import os
import signal
import hashlib

TOKEN = "" #Bot Token Here
USER_ID = 0 #Discord Profile UserID Here

AUDIO_DIR = "./Audio" #Not Yet Implemented
PFP_DIR = "./PFP" #Not Yet Implemented
#TODO: make MUSIC_FILE, NEW_BOT_NAME, and NEW_PROFILE_PIC_PATH chosen at runtime
MUSIC_FILE = "" #Music File Name Here
NEW_BOT_NAME = "" #Nickname To Change To
NEW_PROFILE_PIC_PATH = "" #Filepath to New Profile Picture

#Old bot identity for restoration
OLD_BOT_NAME = "" #Nickname To Revert To
OLD_PROFILE_PIC_PATH = "" #Filepath to Profile Picture to Revert To

LIMITED_ACTIONS_ENABLED = True  # Set to False to prevent name/profile changes

intents = discord.Intents.default()
intents.voice_states = True
intents.guilds = True
intents.messages = True
intents.guild_messages = True
client = discord.Client(intents=intents)

original_name = None
original_avatar = None
voice_client = None
text_channels = {}
skip_username_revert = False
skip_avatar_revert = False
music_muted = False  # Mute state


async def restore_bot():
    #Restores the bot's original name and profile picture before exiting, if hasn't been rate-limited.
    global skip_username_revert, skip_avatar_revert

    if not LIMITED_ACTIONS_ENABLED:
        print("Skipping identity restoration due to LIMITED_ACTIONS_ENABLED being False.")
        return

    user = client.user
    if user.name != OLD_BOT_NAME and not skip_username_revert:
        try:
            await user.edit(username=OLD_BOT_NAME)
        except discord.HTTPException as e:
            print(f"Skipping username revert due to rate limit: {e}")

    try:
        with open(OLD_PROFILE_PIC_PATH, "rb") as f:
            old_avatar = f.read()

        await user.edit(avatar=old_avatar)

    except discord.HTTPException as e:
        print(f"Skipping avatar revert due to rate limit: {e}")
    except FileNotFoundError:
        print(f"Error: Old profile picture not found at {OLD_PROFILE_PIC_PATH}")


async def change_bot_identity():
    """Changes the bot's name and profile picture while handling rate limits."""
    global skip_username_revert, skip_avatar_revert

    if not LIMITED_ACTIONS_ENABLED:
        print("Skipping name and profile picture change due to LIMITED_ACTIONS_ENABLED being False.")
        return

    user = client.user

    if user.name != NEW_BOT_NAME:
        try:
            await user.edit(username=NEW_BOT_NAME)
        except discord.HTTPException as e:
            print(f"Skipping username change due to rate limit: {e}")
            skip_username_revert = True

    try:
        with open(NEW_PROFILE_PIC_PATH, "rb") as f:
            new_avatar = f.read()

        await user.edit(avatar=new_avatar)

    except discord.HTTPException as e:
        print(f"Skipping avatar change due to rate limit: {e}")
        skip_avatar_revert = True
    except FileNotFoundError:
        print(f"Error: Profile picture not found at {NEW_PROFILE_PIC_PATH}")


async def find_user_voice_channel():
    """Finds the voice channel where the user is currently in and returns the server (guild) and channel."""
    for guild in client.guilds:
        for vc in guild.voice_channels:
            if vc.name.lower() == "general":
                for member in vc.members:
                    if member.id == USER_ID:
                        return guild, vc
    return None, None


async def join_voice_channel():
    """Joins the 'General' voice channel if the user is in it and loops music."""
    global voice_client
    guild, vc = await find_user_voice_channel()

    if vc:
        if voice_client and voice_client.is_connected():
            print(f"Already connected to {voice_client.channel.name}.")
            return

        print(f"Connecting to voice channel: {vc.name} in {guild.name}")
        voice_client = await vc.connect()

        await loop_music()
    else:
        print("User is not in a 'General' voice channel. Cannot connect.")


async def loop_music():
    """Plays the music file in a loop while respecting the mute toggle."""
    global voice_client, music_muted

    if not voice_client or not voice_client.is_connected():
        print("Voice client is not connected. Cannot play music.")
        return

    if music_muted:
        print("Music is muted. Not playing audio.")
        return

    if voice_client.is_playing():
        print("Music is already playing. Skipping redundant play call.")
        return

    def after_playing(error):
        if error:
            print(f"Error in playing audio: {error}")
        asyncio.run_coroutine_threadsafe(loop_music(), client.loop)

    print("Starting music playback...")
    voice_client.play(discord.FFmpegPCMAudio(MUSIC_FILE), after=after_playing)


async def toggle_mute():
    """Toggles the music between muted and unmuted."""
    global music_muted, voice_client
    music_muted = not music_muted

    if music_muted:
        print("Music muted.")
        if voice_client and voice_client.is_playing():
            voice_client.pause()
    else:
        print("Music unmuted.")
        if voice_client and not voice_client.is_playing():
            voice_client.resume()


async def leave_voice_channel():
    """Forces the bot to leave the current voice channel."""
    global voice_client
    if voice_client and voice_client.is_connected():
        print(f"Disconnecting from {voice_client.channel.name}.")
        await voice_client.disconnect()
        voice_client = None
    else:
        print("Bot is not currently connected to a voice channel.")


async def delete_bot_messages():
    """Deletes only the bot's last 200 messages in each `vc-text` channel."""
    for guild in client.guilds:
        if guild.id in text_channels:
            channel = text_channels[guild.id]
            try:
                count = 0
                async for message in channel.history(limit=200):
                    if message.author == client.user:
                        await message.delete()
                        count += 1
                        await asyncio.sleep(1.2)
                print(f"Deleted {count} messages in {channel.name} on {guild.name}.")
            except discord.Forbidden:
                print(f"Missing permissions to delete messages in {channel.name} on {guild.name}.")
            except discord.HTTPException as e:
                print(f"Failed to delete messages in {channel.name} on {guild.name}: {e}")


async def handle_terminal():
    """Handles terminal input for sending messages, erasing bot messages, or managing voice connections."""
    print("Commands Available: cancel | erase | connect | disconnect | mute")

    while True:
        message = await asyncio.to_thread(input, "> ")

        if message.lower() == "cancel":
            print("Deleting messages before canceling...")
            await delete_bot_messages()
            print("Cancelling and restoring bot identity...")
            await restore_bot()
            await leave_voice_channel()
            await client.close()
            return

        elif message.lower() == "erase":
            print("Deleting last 200 messages in each `vc-text` channel...")
            await delete_bot_messages()

        elif message.lower() == "connect":
            print("Connecting to voice channel...")
            await join_voice_channel()

        elif message.lower() == "disconnect":
            print("Disconnecting from voice channel...")
            await leave_voice_channel()

        elif message.lower() == "mute":
            await toggle_mute()

        elif message:
            guild, vc = await find_user_voice_channel()
            if guild and vc and guild.id in text_channels:
                #formatted_message = f"**{message.upper()}**" #Uncomment for capitalized messages
                await text_channels[guild.id].send(message)


@client.event
async def on_ready():
    """Runs when the bot connects to Discord."""
    global text_channels
    print(f"Logged in as {client.user}")

    await change_bot_identity()

    for guild in client.guilds:
        for channel in guild.text_channels:
            if channel.name == "vc-text":
                text_channels[guild.id] = channel
                print(f"vc-text channel found in {guild.name}")

    await join_voice_channel()
    await handle_terminal()


client.run(TOKEN)
