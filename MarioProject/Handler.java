

public class Handler {
	public SoundEffect sound;
	
	public Player player;
	public Enemy[] enemies = new Enemy[C.numEnemies];
	public BlockNormal[] blk_normal = new BlockNormal[C.GameLength];
	public Health health;
	public UnsignedCounter score;
	
	public ThreadAnimation t_animation;
	public ThreadMovement t_movement;
	public ThreadShooting t_shooting;
	public ThreadCollision t_collision;
	public ThreadHealthCheck t_gamecheck;
	
	public Handler(){
		sound = new SoundEffect();
		player = new Player(this);
		for (int i = 0; i < enemies.length; i++){
			enemies[i] = new Enemy(this, (i+1)*Dim.WIDTH, Dim.HEIGHT-Dim.UNIT_H-100);
		}
		this.scan_block_file();
		health = new Health(20);
		score = new UnsignedCounter(0);
		
		t_animation = new ThreadAnimation(this);
		t_movement = new ThreadMovement(this);
		t_shooting = new ThreadShooting(this);
		t_collision = new ThreadCollision(this);
		t_gamecheck = new ThreadHealthCheck(this);
	}
	private void scan_block_file(){
		try{
			int tmp = 5/0;
			// scan files			
			
		}catch(Exception ex){
			this.default_blocks(0, C.GameLength);
		}
	}
	private void default_blocks(int start, int end){
		for (int i = start; i < end; i++){
			this.blk_normal[i] = new BlockNormal(i*Dim.UNIT_W, Dim.HEIGHT-Dim.UNIT_H);
		}
	}
	
	public void start_game_threads(){
		t_animation.start();
		t_movement.start();
		t_shooting.start();
		t_collision.start();
		t_gamecheck.start();
	}
}
