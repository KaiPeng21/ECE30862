

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.List;
import java.util.Iterator;

public class Game extends JFrame implements ActionListener{
	private static final long serialVersionUID = 1L;
	public Timer timer = new Timer(C.timval,this);
	public JPanel panel = new JPanel();
	public JLabel scoreText = new JLabel("Score: " + 0);
	public JLabel healthText = new JLabel("Health: " + C.initHealh);
	public Handler H;
	
	public Game(){
		this.GUI_setup();
		this.label_setup();
		ImgPool.image_setup();
		this.play();
	}
	public void play(){
		H = new Handler();
		timer.start();
		H.start_game_threads();
	}
	
	private void GUI_setup(){
		this.setTitle("30862 Project");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		this.setSize(Dim.WIDTH, Dim.HEIGHT);
		this.setResizable(false);
		this.setIgnoreRepaint(true);
		this.addKeyListener(new Key());
	}
	private void label_setup(){
		this.panel.setLayout(new FlowLayout(FlowLayout.LEFT));
		this.scoreText.setFont(new Font("Dialog", Font.PLAIN, 30));
		this.panel.add(this.scoreText);
		this.healthText.setFont(new Font("Dialog", Font.PLAIN, 30));
		this.panel.add(this.healthText);
		this.panel.setAlignmentX(LEFT_ALIGNMENT);
		this.add(panel);
	}
	
	
	@Override
	public void actionPerformed(ActionEvent e){
		if (e.getSource() == timer){
			this.repaint();
			this.label_update();
		}
	}
	public void label_update(){
		try{
			this.healthText.setText("Health: " + H.health.toString());
			this.scoreText.setText("Score: " + H.score.toString());
		}catch(NullPointerException ex){}
	}
	
	
	@Override
	public void update(Graphics g){
		paint(g);
	}
	
	@Override
	public void paint(Graphics g){
		Image offScreenImage = this.createImage(Dim.WIDTH, Dim.HEIGHT);
		Graphics gImage = offScreenImage.getGraphics();	
		gImage.setFont(new Font("Dialog", 24,0));
		gImage.setColor(new Color(0,110,255,50));
		
		super.paint(gImage);
		this.paint_background(gImage);
		// Put your painted object here
		
		
		try{
			this.draw_component(gImage, H.player);
		}catch(Exception ex){}
		try{
			this.draw_component(gImage, H.player.blist);
		}catch(Exception ex){}
		try{
			this.draw_component(gImage, H.enemies);
		}catch(Exception ex){}
		try{
			this.draw_component(gImage, H.blk_normal);
		}catch(Exception ex){}
		try{
			for (int i = 0; i < H.enemies.length; i++){
				try{
					this.draw_component(gImage, H.enemies[i].blist);
				}catch(Exception ex){}
			}
		}catch(Exception ex){}
		//gImage.drawImage(H.player.img, H.player.x_int(), H.player.y_int(), H.player.w(), H.player.h(), this);
		
		
		
		
		
		
		g.drawImage(offScreenImage,0,0,null);
		g.dispose();
	}
	public void paint_background(Graphics g){
		try{
			g.fillRect(0, 0, Dim.WIDTH, Dim.HEIGHT);
		}catch(Exception ex){}
	}
	public void draw_component(Graphics gImage, Component o){
		try{
			if (o.facing() == C.Right){
				gImage.drawImage(o.img, o.x_int(), o.y_int(), o.w(), o.h(), this);
			}else{
				gImage.drawImage(o.img, o.x_int()+o.w(), o.y_int(), -o.w(), o.h(), this);
			}
		}catch(Exception ex){}			
	}
	public void draw_component(Graphics gImage, Component[] list){
		for (int i = 0; i < list.length; i++){
			draw_component(gImage, list[i]);
		}
	}
	public void draw_component(Graphics gImage, List<Bullet> list){
		synchronized(list){
			Iterator<Bullet> iter = list.iterator();
			while(iter.hasNext()){
				Bullet tmp = iter.next();
				if (tmp.is_active()){
					draw_component(gImage, tmp);
				}
			}
		}
		
	}
	
	class Key extends KeyAdapter{
		public Key(){
		}
		@Override
		public void keyPressed(KeyEvent e){
			H.player.keyPressed(e);
		}
		@Override
		public void keyReleased(KeyEvent e){
			H.player.keyReleased(e);
		}
	}
}
