

import java.io.File;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;

public class SoundEffect {
	public static final int Size = 4;
	public static final int PlayerGotHit = 0;
	public static final int PlayerShoot = 1;
	public static final int EnemyGotHit = 2;
	public static final int EnemyShoot = 3;
	private AudioInputStream[] stream = new AudioInputStream[Size];
	private Clip[] clip = new Clip[Size];
		
	public SoundEffect(){
		this.music_file_read();
	}
	private void music_file_read(){
		try{
			stream[PlayerGotHit] = AudioSystem.getAudioInputStream(new File("sound/effect_player_gothit.wav"));
		}catch(Exception ex){}
		try{
			stream[PlayerShoot] = AudioSystem.getAudioInputStream(new File("sound/effect_player_shoot.wav"));
		}catch(Exception ex){}
		try{
			stream[EnemyGotHit] = AudioSystem.getAudioInputStream(new File("sound/effect_enemy_gothit.wav"));
		}catch(Exception ex){}
		try{
			stream[EnemyShoot] = AudioSystem.getAudioInputStream(new File("sound/effect_enemy_shoot.wav"));
		}catch(Exception ex){}	
		
		for (int i = 0; i < SoundEffect.Size; i++){
			try{
				clip[i] = AudioSystem.getClip();
				clip[i].open(stream[i]);
				clip[i].loop(1);
				clip[i].stop();
				clip[i].setFramePosition(0);
			}catch(Exception ex){}
		}
	}
	
	public void play(int index){
		try{
			clip[index].setFramePosition(0);
			clip[index].start();
		}catch(Exception ex){}
	}
	public void stop(){
		for (int i = 0; i < SoundEffect.Size; i++){
			clip[i].stop();
			clip[i].setFramePosition(0);
		}
	}
}
