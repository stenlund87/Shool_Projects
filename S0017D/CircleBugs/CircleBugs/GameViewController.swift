//
//  GameViewController.swift
//  CircleBugs
//
//  Created by sdev on 2017-10-18.
//  Copyright © 2017 gscept. All rights reserved.
//

import UIKit
import SpriteKit
import GameplayKit

class GameViewController: UIViewController
{

    @IBOutlet weak var submitButton: UIButton!
    
    
    @IBAction func HighscoreButton(_ sender: AnyObject)
    {       
        GameScene(fileNamed: "GameScene")?.setHighscoreButton(nameText.text!, highscore)
    }
    @IBOutlet weak var nameText: UITextField!
    @IBOutlet weak var highscoreText: UITextView!
    @IBOutlet weak var windowView: UIView!
    var highscore:Double = 0.0
    override func viewDidLoad()
    {
        super.viewDidLoad()
        
        // Get the SKScene from the loaded GKScene
        if let view = self.view as! SKView?
        {
            if let scene = GameScene(fileNamed: "GameScene")
            {
                submitButton.isHidden = true
                nameText.isHidden = true
                highscoreText.isHidden = true
                scene.scaleMode = .aspectFill
                scene.controller = self
                view.presentScene(scene)
                scene.spawnBugs()
                scene.startTime = NSDate()
            }
            
            
            view.ignoresSiblingOrder = true
            
            view.showsFPS = true
            view.showsNodeCount = true
        }
        
        // Load 'GameScene.sks' as a GKScene. This provides gameplay related content
        // including entities and graphs.
           }

    override var shouldAutorotate: Bool
    {
        return true
    }

    override var supportedInterfaceOrientations: UIInterfaceOrientationMask
    {
        if UIDevice.current.userInterfaceIdiom == .phone
        {
            return .allButUpsideDown
        }
        else
        {
            return .all
        }
    }

    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Release any cached data, images, etc that aren't in use.
    }

    override var prefersStatusBarHidden: Bool
    {
        return true
    }
}
