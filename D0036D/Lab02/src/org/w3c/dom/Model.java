/*
 * 
 */
package org.w3c.dom;


import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;

import java.text.ParseException;
import java.text.SimpleDateFormat;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import org.w3c.dom.Element;

import java.io.File;
import java.util.Calendar;
import java.util.Date;



import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;

import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;


// TODO: Auto-generated Javadoc
/**
 * Class Model
 * Handles all the data from an XML-file.
 */
public class Model 
{
	/**
	 * String arrays to sort out the data from places.xml
	 */
	public String[] cityArr = new String[3];
	
	/** The long arr. */
	public String[] longArr = new String[3];
	
	/** The lat arr. */
	public String[] latArr = new String[3];
	
	/** The alt arr. */
	public String[] altArr = new String[3];
	
	public String[] expirationDateArr = new String[100];
	
	/** The expiration arr. */
	public String[] expirationArr = {"1","5","10","60"};
	
	/** The cache destroyer. */
	public String cacheDestroyer = "";
	
	public String expirationDate = "";
	
	/** Arrays to handle when each cache will be renewed. */
	public long[] timeToLive = new long[3];
	
	/** The time left. */
	public long[] timeLeft = new long[3];
	
	/** Array is each cache is expired. */
	public boolean[] expiredArr = new boolean[3];


	
	/**
	 * Method to update the weather at given location and time.
	 *
	 * @param filename the filename
	 * @param index the index
	 * @param selectedTime the selected time
	 * @return String, a string that is used for showing the user the current weather at the location
	 * @throws ParseException 
	 */
	public String UpdateWeather(String filename, int index, String selectedTime) throws ParseException 
	{	
		IsExpired(index);
		
		try
		{
			if(expiredArr[index])
			{
				expirationDate = "";
				URL url = new URL("http://api.met.no/weatherapi/locationforecast/1.9/?lat="+latArr[index]+";lon="+longArr[index]+";msl="+altArr[index]);
				URLConnection conn = url.openConnection();
				
				DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
				DocumentBuilder builder = factory.newDocumentBuilder();
				
				Document doc = builder.parse(conn.getInputStream());
				TransformerFactory tfactory = TransformerFactory.newInstance();
				Transformer xform = tfactory.newTransformer();
				
				File myOutput = new File(filename+".xml");
				xform.transform(new DOMSource(doc), new StreamResult(myOutput));
				
				timeToLive[index] += System.currentTimeMillis();
				expirationDateArr[index] = GetExpirationDate(timeToLive[index], "yyyy/MM/dd-HH:mm:ss.SSS");
				
				System.out.println("Hämtar data för: "+ filename);
				
				expiredArr[index] = false;

				return UpdateWeather(filename, index, selectedTime);
			}
			else
			{
				String tempString = "";
				DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();

				DocumentBuilder builder = factory.newDocumentBuilder();
				Document doc = builder.parse(filename+".xml");
				NodeList tempList = doc.getElementsByTagName("temperature");
						
				for(int i = 0; i<24; i++)
					{
						Node tempNode = tempList.item(i);
						Element temperature = (Element) tempNode;
						Node timeNode = tempNode.getParentNode().getParentNode();
						Element time = (Element)timeNode;
						String koll = time.getAttributeNode("from").toString().substring(17, 22);
						
						if(koll.equals(selectedTime))
						{
							tempString ="Temperaturen för "+filename+" klockan "+selectedTime +" är, "+temperature.getAttribute("value")+" grader";
							break;
						}
						else
						{
							tempString ="Tiden du har angett går ej att finna!!                      ";
						}
					}	
				return tempString;
				}
				}
				catch(SAXException e)
				{
					e.printStackTrace();
				}
				catch(IOException e)
				{
					e.printStackTrace();	
				}
				catch (ParserConfigurationException e) 
				{
					e.printStackTrace();
				}
				catch(NullPointerException e)
				{
					e.printStackTrace();
				}
				catch (TransformerException e)
				{
					e.printStackTrace();
				}
				return "";

		}

	/**
	 * Method for getting locations for the GUI so the user can choose from a list.
	 */
	public void GetLocation()
	{
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try
		{
			DocumentBuilder builder = factory.newDocumentBuilder();
			Document doc = builder.parse("places.xml");
			NodeList cityList = doc.getElementsByTagName("locality");
			for(int i = 0; i<cityList.getLength(); i++)
			{
				Node cityNode = cityList.item(i);
				if(cityNode.getNodeType()==Node.ELEMENT_NODE)
				{
					Element city = (Element) cityNode;
					String place =  city.getAttribute("name");
					cityArr[i] = place;
					NodeList altList = city.getChildNodes();
					
					for(int j = 0; j<altList.getLength(); j++)
					{
						Node alt = altList.item(j);
						if(alt.getNodeType() == Node.ELEMENT_NODE)
						{
							Element altitude = (Element)alt;
							longArr[i] = altitude.getAttribute("longitude");
							latArr[i] = altitude.getAttribute("latitude");
							altArr[i] = altitude.getAttribute("altitude");
							expirationDateArr[i] = altitude.getAttribute("date");
						}
					}				
				
				}
			}
		}
		catch(SAXException e)
		{
			e.printStackTrace();
		}
		catch(IOException e)
		{
			e.printStackTrace();	
		}
		catch (ParserConfigurationException e) 
		{
			e.printStackTrace();
		}
		catch(NullPointerException e)
		{
			e.printStackTrace();
		} 
	
	}
	
	public void SetCacheToFile()
	{
		try
		{
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder builder = dbf.newDocumentBuilder();
			Document doc = builder.newDocument();
			Element root = doc.createElement("places");
			doc.appendChild(root);
			for(int i = 0; i<expiredArr.length; i++)
			{
	
				Element loc = doc.createElement("locality");
				root.appendChild(loc);
				
				Attr name = doc.createAttribute("name");
				name.setValue(cityArr[i]);
				loc.setAttributeNode(name);
				
				Element location = doc.createElement("location");
				loc.appendChild(location);
				
				Attr exp = doc.createAttribute("date");
				exp.setValue(expirationDateArr[i]);
				location.setAttributeNode(exp);
				
				Attr lon = doc.createAttribute("longitude");
				lon.setValue(longArr[i]);
				location.setAttributeNode(lon);
				
				Attr lat = doc.createAttribute("latitude");
				lat.setValue(latArr[i]);
				location.setAttributeNode(lat);
				
				Attr alt = doc.createAttribute("altitude");
				alt.setValue(altArr[i]);
				location.setAttributeNode(alt);
			}
			
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			DOMSource source = new DOMSource(doc);
			StreamResult result = new StreamResult(new File("places.xml"));
			transformer.transform(source, result);

			System.out.println("File saved!");

			
		}
		catch (ParserConfigurationException pce)
		{
			pce.printStackTrace();
		} catch (TransformerException tfe)
		{
			tfe.printStackTrace();
		}
	}
	
	/**
	 * Method to check if a chosen cache is out of date.
	 *
	 * @param index the index
	 * @throws ParseException 
	 */
	public void IsExpired(int index) throws ParseException
	{	
		try
		{
			SimpleDateFormat formatter = new SimpleDateFormat("yyyy/MM/dd-HH:mm:ss.SSS");
			String oldTime = expirationDateArr[index];
			Date oldDate = formatter.parse(oldTime);
			Date newDate = new Date();
			Calendar currentDate = Calendar.getInstance();
			currentDate.setTime(newDate);
			
			Calendar oldOld = Calendar.getInstance();
			oldOld.setTime(oldDate);
			

			if(currentDate.after(oldOld))
			{
				expiredArr[index] = true;
			}
			
//			if(oldDate.compareTo(newDate)<=0)
//			{
//				expiredArr[index] = true;
//			}
			else
			{
				expiredArr[index] = false;
			}
			
		}
		catch(IllegalArgumentException e)
		{
			e.printStackTrace();
		}
	}
	
	public String GetExpirationDate(long millisec, String format)
	{
		SimpleDateFormat formatter = new SimpleDateFormat(format);
		Calendar currentDate = Calendar.getInstance();
		currentDate.setTimeInMillis(millisec);
		
		return formatter.format(currentDate.getTime());
	}
}



