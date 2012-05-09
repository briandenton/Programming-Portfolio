/**
 * MainFrame java file.
 *
 * @author Brian Denton
 */
 
 import javax.swing.*;
 import java.awt.*;
 import java.awt.event.*;
 
 class MainFrame extends JFrame implements ActionListener{
 
    public static final int FRAME_POSITION_X = 200;
    public static final int FRAME_POSITION_Y = 150;
    
    public static final int GRID_SIZE = 10;
    
    private JPanel statusPanel;
 
    private JButton bFace;
    private ImageIcon bFaceIcon;
    private JLabel counter;
    private GamePanel gamePanel;
    private GameMaster master;
    private JMenuBar mb;
    private JMenu mGame;
    private JMenu mHelp;
    private JMenuItem miAbout;
    private JMenuItem miEasy;
    private JMenuItem miExit;
    private JMenuItem miHard;
    private JMenuItem miMiddle;
    private Container contentPane;
    
    public static int numMine = 10; //Beginner is default
 
    MainFrame(){
    
        contentPane = getContentPane( );
        contentPane.setLayout( new BorderLayout() ); 
        
        //set the frame properties
        setTitle( "Minesweeper" );
        setLocation( FRAME_POSITION_X, FRAME_POSITION_Y );
        setResizable( false );
    
        //Create menu bar
        mb = new JMenuBar();
        
        //Add Game menu
        mGame = new JMenu( "Game" );
        mb.add( mGame );
        mGame.addActionListener( this );
        
        miEasy = new JMenuItem( "Beginner" );
        mGame.add( miEasy );
        miEasy.addActionListener( this );

        miMiddle = new JMenuItem( "Intermediate" );
        mGame.add( miMiddle );
        miMiddle.addActionListener( this );

        miHard = new JMenuItem( "Advanced" );
        mGame.add( miHard );
        miHard.addActionListener( this );

        miExit = new JMenuItem( "Exit" );
        mGame.add( new JSeparator() );
        mGame.add( miExit );
        miExit.addActionListener( this );
        
        //Add Help menu
        mHelp = new JMenu( "Help" );
        mb.add( mHelp );
        mHelp.addActionListener( this );
        
        miAbout = new JMenuItem( "About..." );
        mHelp.add( miAbout );
        miAbout.addActionListener( this );
        
        mb.add( mGame );
        mb.add( mHelp );
        setJMenuBar( mb );
        
        //Add mine counter label
        statusPanel = new JPanel( new FlowLayout() );
        String labelString = new String("Left: " + numMine );
        counter = new JLabel( labelString );
        statusPanel.add( counter );
        
        //Add game-status button
        bFaceIcon = new ImageIcon( "SMILE.GIF" );
        bFace = new JButton( bFaceIcon );
        bFace.setPreferredSize( new Dimension( 26, 27 ) );
        statusPanel.add( bFace );
        bFace.addActionListener( this );

        contentPane.add( statusPanel, BorderLayout.NORTH );

        //Add game panel
        
        master = new GameMaster( GRID_SIZE, GRID_SIZE );
        gamePanel = new GamePanel( master, this );
        contentPane.add( gamePanel, BorderLayout.CENTER );
        pack();
        
        //register 'Exit upon closing' as a default close operation
        setDefaultCloseOperation( EXIT_ON_CLOSE );   
    
    }
    
    public void actionPerformed(ActionEvent event){
    
        if( event.getSource() instanceof JButton ){
            System.out.print("JButton");
            startGame();
     
        }
        
        else if( event.getSource() instanceof JMenuItem ){
        
            JMenuItem selectedMenuItem = (JMenuItem) event.getSource();
            
            if( selectedMenuItem.getText().equals( "Beginner" ) ){

                numMine = 10;
                startGame();
            
            }
            
            else if( selectedMenuItem.getText().equals( "Intermediate" ) ){

                numMine = 20;
                startGame();
            
            }
            
            else if( selectedMenuItem.getText().equals( "Advanced" ) ){

                numMine = 30;
                startGame();
            
            }
            
            else if( selectedMenuItem.getText().equals( "About..." ) ){

                JOptionPane.showMessageDialog(null,"Brian Denton\nCS 180 Project 6\nApril 1, 2009");
            
            }

            else if( selectedMenuItem.getText().equals( "Exit" ) ){

                System.exit(0);
            
            }
        }
    
    }

    public void mouseClicked(){

        startGame();

    }
    
    public void mouseEntered(){

        //Nothing to do in the project

    }
    
    public void mouseExited(){

        //Nothing to do in the project

    }
    
    public void mousePressed(){

        ImageIcon bFaceIcon = new ImageIcon( "Ooo.gif" );
        bFace.setIcon( bFaceIcon );
        gamePanel.refreshPanel(); 

    }


    public void mouseReleased(){

        ImageIcon bFaceIcon = new ImageIcon( "SMILE.GIF" );
        bFace.setIcon( bFaceIcon );
        gamePanel.refreshPanel();        
    
    }

    private void startGame(){
      
        master.gameState = State.INPROCESS;
        master.setMines( numMine );
        setCounter( numMine );
        bFace.setIcon( new ImageIcon( "SMILE.GIF" ) );
        gamePanel.refreshPanel();
    
    }
    
    public void setCounter(int value){
    
        counter.setText("Left: " + value );
        
    }
    
    public void setLoseFace(){
    
        bFace.setIcon(new ImageIcon( "LOSE.GIF" ) );
        master.gameState = State.LOSE;
        
    }
          
          
    public void setWinFace(){
    
        bFace.setIcon(new ImageIcon( "WIN.GIF" ) );
        master.gameState = State.WIN;

    }
    
    
}
