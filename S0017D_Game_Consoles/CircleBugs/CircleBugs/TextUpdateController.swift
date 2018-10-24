//
//  TextUpdateController.swift
//  CircleBugs
//
//  Created by sdev on 2017-10-24.
//  Copyright © 2017 gscept. All rights reserved.
//

import Foundation
import UIKit
import SpriteKit

class TextUpdateController: UIViewController
{
    
    @IBOutlet weak var textfield: UITextView!
    var userDefault = UserDefaults.standard
    override func viewDidLoad()
    {
        super.viewDidLoad()
        var string:String  = String()
        string = string + String(userDefault.value(forKey: "H1Player") as! String) + "\n"
        string = string + String(userDefault.double(forKey: "H1")) + "\n" + "\n"
        
        string = string + String(userDefault.value(forKey: "H2Player") as! String) + "\n"
        string = string + String(userDefault.double(forKey: "H2")) + "\n" + "\n"
        
        string = string + String(userDefault.value(forKey: "H3Player") as! String) + "\n"
        string = string + String(userDefault.double(forKey: "H3")) + "\n" + "\n"
        
        textfield.text = string
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
