//
//  GameScene.swift
//  CircleBugs
//
//  Created by sdev on 2017-10-18.
//  Copyright © 2017 gscept. All rights reserved.
//

import SpriteKit
import GameplayKit

struct bug
{
    init()
    {}
    var team:String = ""
    var image:UIImage? = nil
    var position:CGPoint = CGPoint(x:0,y:0)
}

struct finger
{
    init()
    {
        id = ""
    }
    init(from touchID:String)
    {
        id = touchID
    }

    var id:String
    var path = UIBezierPath()
    var shapeLayer = CAShapeLayer()
    var points:[CGPoint] = []
    var intersect = false
}


class GameScene: SKScene
{
    weak var controller:GameViewController?
    var bugs:[SKSpriteNode] = []
    private var lastUpdateTime : TimeInterval = 0
    var touchingFingers:[finger] = [finger(),finger()]
    var background = SKSpriteNode(imageNamed: "ground")
    
    var redTeamBugs = 5
    var blueTeamBugs = 5
    var greenTeamBugs = 5
    var whiteTeamBugs = 5
    var yellowTeamBugs = 5
    var startTime = NSDate()
    var endTime = NSDate()
    
    let userDefault = UserDefaults.standard
    
    func checkStatus()
    {
        //userDefault.set(nil, forKey: "H1Player")
        var value = userDefault.string(forKey: "H1Player")
        if value == nil
        {
            userDefault.set(1000.0, forKey: "H3")
            userDefault.set(1000.0, forKey: "H2")
            userDefault.set(1000.0, forKey: "H1")
            
            userDefault.set("Player3", forKey: "H3Player")
            userDefault.set("Player2", forKey: "H2Player")
            userDefault.set("Player1", forKey: "H1Player")
            print("Setting default values")
        }
    }
    
    func spawnBugs()
    {
        background.zPosition = 10
        self.addChild(background)
        checkStatus()
        var i = 0
        
        while i < 25
        {
            
            let xPos = Int(arc4random_uniform(600))-300
            let yPos = Int(arc4random_uniform(800))-400
            
            var bug = SKSpriteNode()

            if i < 5
            {
                bug = SKSpriteNode(imageNamed: "red-ladybugs-hi.png")
                bug.name = "RED"
            }
            else if (i > 4) && (i < 10)
            {
                bug = SKSpriteNode(imageNamed: "blue-ladybugs-hi.png")
                bug.name = "BLUE"
            }
            else if (i > 9) && (i < 15)
            {
                bug = SKSpriteNode(imageNamed: "green-ladybugs-hi.png")
                bug.name = "GREEN"
            }
            else if (i > 14) && (i < 20)
            {
                bug = SKSpriteNode(imageNamed: "white-ladybugs-hi.png")
                bug.name = "WHITE"
            }
            else if (i > 19) && (i < 25)
            {
                bug = SKSpriteNode(imageNamed: "yellow-ladybugs-hi.png")
                bug.name = "YELLOW"
            }
            
            bug.setScale(0.1)
            bug.position = CGPoint(x: xPos, y:yPos)
            bug.zPosition = 1
            bugs.append(bug)
            background.addChild(bug)
            
            i+=1
        }
    }
    
    
    func touchDown(atPoint pos : CGPoint)
    {
        
    }
    
    func touchMoved(toPoint pos : CGPoint)
    {

    }
    
    func touchUp(atPoint pos : CGPoint)
    {

    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        super.touchesBegan(touches, with: event)

        for touch in touches
        {
            var f = finger(from: String(format: "%p",touch))
            var i = 0
            while i < 2
            {
                if touchingFingers[i].id == ""
                {
                    f.path.move(to: touch.location(in: self.view))
                    f.points.append(touch.location(in: self.view))
                    touchingFingers[i] = f
                    break
                }
                i += 1
            }
        }
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        super.touchesMoved(touches, with: event)
        for touch in touches
        {
            for var f in 0...touchingFingers.count-1
            {
                if touchingFingers[f].id == String(format: "%p", touch)
                {
                    touchingFingers[f].path.addLine(to: touch.location(in: self.view))
                    touchingFingers[f].points.append(touch.location(in: self.view))
                    if(touchingFingers[f].points.count >= 4 )
                    {
                        for var p in 0...touchingFingers[f].points.count - 4
                        {
                            if checkLineIntersect(touchingFingers[f].points[p], touchingFingers[f].points[p+1], touchingFingers[f].points[touchingFingers[f].points.count - 2], touchingFingers[f].points[touchingFingers[f].points.count - 1])
                            {
                                print("FUCK YOU")
                                touchingFingers[f].intersect = true
                                let time = DispatchTime.now()
                                //drawLines(fi:touchingFingers[f], fill:true)
                                DispatchQueue.main.asyncAfter(deadline: time)
                                {
                                    self.touchingFingers[f].shapeLayer.removeFromSuperlayer()
                                    self.touchingFingers[f].id = ""
                                    self.touchingFingers[f].points = []
                                    self.touchingFingers[f].intersect = false
                                }
                                break
                            }
                        }
                    }
                    drawLines(fi:touchingFingers[f], fill:false)
                    break
                }
            }
        }
    }
    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
    {
        super.touchesEnded(touches, with: event)
        let time = DispatchTime.now()+0.3
        for touch in touches
        {
            var i = 0
            while i < 2
            {
                if touchingFingers[i].id == String(format: "%p", touch)
                {
                    drawLines(fi:touchingFingers[i], fill:true)
                    DispatchQueue.main.asyncAfter(deadline: time)
                    {
                        self.touchingFingers[i].shapeLayer.removeFromSuperlayer()
                        self.touchingFingers[i].id = ""
                        self.touchingFingers[i].points = []
                        self.touchingFingers[i].intersect = false
                    }
                    break
                }
                i+=1
            }
        }
    }
    
    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?)
    {
    }

    func drawLines(fi: finger, fill:Bool)
    {

        //let shapeLayer = CAShapeLayer()
        fi.shapeLayer.strokeColor = UIColor.red.cgColor
        if fill
        {
            fi.shapeLayer.fillColor = UIColor.red.cgColor
            fi.shapeLayer.opacity = 0.7
            fi.path.close()
            if !fi.intersect && (controller?.nameText.isHidden)!
            {
                bugsInside(fi: fi)
            }
            
        }
        else
        {
             fi.shapeLayer.fillColor = UIColor.clear.cgColor
        }
        
        fi.shapeLayer.path = fi.path.cgPath
        controller?.windowView.layer.addSublayer(fi.shapeLayer)
    }
    
    func bugsInside(fi: finger)
    {
        var indexArr:[Int] = []
        for i in 0...bugs.count-1
        {
            if fi.path.contains(convertPoint(toView: bugs[i].position))
            {
                indexArr.append(i)
               print(bugs[i].name)
            }
        }
        if indexArr.count > 1
        {
            for j in 0...indexArr.count-2
            {
                if bugs[indexArr[j]].name != bugs[indexArr[j+1]].name
                {
                    return
                }
            }
            for k in 0...indexArr.count-2
            {
                bugs[indexArr[indexArr.count-1]].xScale += bugs[indexArr[k]].xScale
                bugs[indexArr[indexArr.count-1]].yScale += bugs[indexArr[k]].yScale
                bugs[indexArr[k]].position = CGPoint(x:1000,y:1000)
                bugs[indexArr[k]].removeFromParent()
                
                if bugs[indexArr[k]].name == "RED"
                {
                    redTeamBugs -= 1
                }
                if bugs[indexArr[k]].name == "BLUE"
                {
                    blueTeamBugs -= 1
                }
                if bugs[indexArr[k]].name == "GREEN"
                {
                    greenTeamBugs -= 1
                }
                if bugs[indexArr[k]].name == "WHITE"
                {
                    whiteTeamBugs -= 1
                }
                else if bugs[indexArr[k]].name == "YELLOW"
                {
                    yellowTeamBugs -= 1
                }
            }
        }
        
        if redTeamBugs == 1
        {
            print("Red team wins!")
            endTime = NSDate()
            setHighscore()
        }
        else if blueTeamBugs == 1
        {
            print("Blue team wins!")
            endTime = NSDate()
            setHighscore()
        }
        else if greenTeamBugs == 1
        {
            print("Green team wins!")
            endTime = NSDate()
            setHighscore()
        }
        else if whiteTeamBugs == 1
        {
            print("White team wins!")
            endTime = NSDate()
            setHighscore()
        }
        else if yellowTeamBugs == 1
        {
            print("Yellow team wins!")
            endTime = NSDate()
            setHighscore()
        }
    }
    
    func moveBugs()
    {
        for i in 0...bugs.count-1
        {
            if bugs[i].position.x != 1000
            {
                var temp = bugs[i].position
                var dx = Int(arc4random_uniform(7)) - 3
                var dy = Int(arc4random_uniform(7)) - 3
            
                if Int(temp.x) + dx > 320 || Int(temp.x) + dx < -320
                {
                    dx *= -1
                }
                if Int(temp.y) + dy > 420 || Int(temp.y) + dy < -420
                {
                    dy *= -1
                }
                
                dx += Int(temp.x)
                dy += Int(temp.y)
                
            
                bugs[i].position = CGPoint(x: dx, y: dy)
            }
        }
    }
    
    func checkLineIntersect(_ p0: CGPoint,_ p1: CGPoint,_ p2: CGPoint,_ p3: CGPoint)->Bool
    {
        if(p1 == p2)
        {
            return false
        }
        var det = (p3.y - p2.y) * (p1.x - p0.x) - (p3.x - p2.x) * (p1.y - p0.y)
        var ua = (p3.x - p2.x) * (p0.y - p2.y) - (p3.y - p2.y) * (p0.x - p2.x)
        var ub = (p1.x - p0.x) * (p0.y - p2.y) - (p1.y - p0.y) * (p0.x - p2.x)
        if det < 0
        {
            ua = -ua
            ub = -ub
            det = -det
        }
        if (ua >= 0.0 && ua <= det && ub >= 0.0 && ub <= det && det != 0)
        {
            return true
        }
        return false
    }
    
    func setHighscore()
    {
        controller?.highscore = endTime.timeIntervalSince(startTime as Date)
        controller?.highscoreText.isHidden = false
        controller?.nameText.isHidden = false
        controller?.submitButton.isHidden = false
        controller?.highscoreText.text = "Your score is: \n" + String(format: "%.3f", (controller?.highscore)!)
    }
    
    func setHighscoreButton(_ name:String, _ score:Double)
    {
        var temp:Double
        var tempName:String

        if score < userDefault.double(forKey: "H3")
        {
            userDefault.set(score, forKey: "H3")
            userDefault.set(name, forKey: "H3Player")
        }
        
        if score < userDefault.double(forKey: "H2")
        {
            temp = userDefault.double(forKey: "H2")
            tempName = userDefault.value(forKey: "H2Player") as! String
            
            userDefault.set(temp, forKey: "H3")
            userDefault.set(tempName, forKey: "H3Player")
            
            userDefault.set(score, forKey: "H2")
            userDefault.set(name, forKey: "H2Player")
        }

        if score < userDefault.double(forKey: "H1")
        {
            temp = userDefault.double(forKey: "H1")
            tempName = userDefault.value(forKey: "H1Player") as! String
            
            userDefault.set(temp, forKey: "H2")
            userDefault.set(tempName, forKey: "H2Player")
            
            userDefault.set(score, forKey: "H1")
            userDefault.set(name, forKey: "H1Player")
        }
    }
    override func update(_ currentTime: TimeInterval)
    {
        // Called before each frame is rendered
        self.lastUpdateTime = currentTime
        if (controller?.nameText.isHidden)!
        {
            moveBugs()
        }
        
    }
}
