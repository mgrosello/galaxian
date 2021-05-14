// JGSoundSystem
//
// Description: A wrapper to abstract the sound stuff. Inspired by a pull
// request from https://github.com/albertzb.
//

package com.spencerseidel;

import java.net.URL;
import java.util.HashMap;
import src.main.java.com.adonax.audiocue.AudioCue;
import src.main.java.com.adonax.audiocue.AudioMixer;
import com.spencerseidel.*;

public class JGSoundSystem {

  protected AudioMixer m_audioMixer;
  protected HashMap<String, AudioCue> m_soundMap;

  public JGSoundSystem() {
    m_soundMap = new HashMap<>();
  }

  public void init() {
    m_audioMixer = new AudioMixer();
    try {
      m_audioMixer.start();
    }
    catch (Exception e) {
      System.err.println("Unable to start audio mixer. " + e.toString());
    }
  }

  public void destroy() {
    for (AudioCue ac : m_soundMap.values()) {
      ac.close();
    }

    m_audioMixer.stop();
  }

  public void loadSound(String name, String path) {
    URL url = this.getClass().getClassLoader().getResource(path);
    try {
      AudioCue newCue = AudioCue.makeStereoCue(url, 5);
      newCue.open(m_audioMixer);
      m_soundMap.put(name, newCue);
    }
    catch (Exception e) {
      System.err.println("Unable to load sound " + path + ". " + e.toString());
    }
  }

  public void stop(String name, int handle) {
    if (handle == -1) {
      return;
    }

    if (m_soundMap.containsKey(name)) {
      AudioCue ac = m_soundMap.get(name);
      if (ac.getIsActive(handle)) {
        ac.stop(handle);
      }
    }
  }

  public int play(String name) {
    if (m_soundMap.containsKey(name)) {
      return m_soundMap.get(name).play();
    }
    else {
      System.err.println("No sound named '" + name + "'");
    }

    return -1;
  }
}
