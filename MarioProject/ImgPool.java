

import java.awt.*;
import java.io.File;

import javax.imageio.ImageIO;

public class ImgPool{
	/*Player*/
	public static int N_player_move = 6;
	public static Image[] player_move = new Image[N_player_move];
	public static int N_player_stand = 2;
	public static Image[] player_stand = new Image[N_player_stand];
	public static int N_player_gothit = 2;
	public static Image[] player_gothit = new Image[N_player_gothit];
	public static int N_enemy_stand = 2;
	public static Image[] enemy_stand = new Image[N_enemy_stand];
	public static int N_enemy_gothit = 2;
	public static Image[] enemy_gothit = new Image[N_enemy_gothit];
	public static Image bullet_player;
	public static Image bullet_enemy;
	public static Image block_normal;
	
	public ImgPool(){
		ImgPool.image_setup();
	}
	
	public static void image_setup(){
		/*Player*/
		try{
			player_move[0] = ImageIO.read(new File("images/player/running/frame-1.png"));
			player_move[1] = ImageIO.read(new File("images/player/running/frame-2.png"));
			player_move[2] = ImageIO.read(new File("images/player/running/frame-3.png"));
			player_move[3] = ImageIO.read(new File("images/player/running/frame-4.png"));
			player_move[4] = ImageIO.read(new File("images/player/running/frame-5.png"));
			player_move[5] = ImageIO.read(new File("images/player/running/frame-6.png"));
		}catch(Exception ex){
			System.out.println("Error loading player move images");
		}
		try{
			player_stand[0] = ImageIO.read(new File("images/player/idle/frame-1.png"));
			player_stand[1] = ImageIO.read(new File("images/player/idle/frame-2.png"));
		}catch(Exception ex){
			System.out.println("Error loaidng player stand images");
		}
		try{
			player_gothit[0] = ImageIO.read(new File("images/player/gothit/frame-1.png"));
			player_gothit[1] = ImageIO.read(new File("images/player/gothit/frame-2.png"));
		}catch(Exception ex){
			System.out.println("Error loading player got hit image");
		}
		
		/*Enemy*/
		try{
			enemy_stand[0] = ImageIO.read(new File("images/enemy/gothit/frame-1.png"));
			enemy_stand[1] = ImageIO.read(new File("images/enemy/gothit/frame-2.png"));
		}catch(Exception ex){
			System.out.println("Error loading enemy stand images");
		}
		try{
			enemy_gothit[0] = ImageIO.read(new File("images/enemy/gothit/frame-1.png"));
			enemy_gothit[1] = ImageIO.read(new File("images/enemy/gothit/frame-2.png"));
		}catch(Exception ex){
			System.out.println("Error loading enemy gothit images");
		}
		
		
		/*Bullet*/
		try{
			bullet_player = ImageIO.read(new File("images/fireball.png"));
		}catch(Exception ex){
			System.out.println("Error loading player bullet image");
		}
		try{
			bullet_enemy = ImageIO.read(new File("images/enemybullet.png"));
		}catch(Exception ex){
			System.out.println("Error loading enemy bullet image");
		}
		
		/*Blocks*/
		try{
			block_normal = ImageIO.read(new File("images/spaceblocks/block_normal.png"));
		}catch(Exception ex){
			System.out.println("Error loading block normal image");
		}
		
	}
	
}
