# TransparencyBug
A bare-bones, stripped-down Win32 application to demonstrate how Microsoft Edge no longer plays well with layered windows.

## Background
In traditional Win32 applications, there are two extended window styles you can set on a window which allow you to create "click through" windows.

They are:

* WS\_EX\_LAYERED
* WS\_EX\_TRANSPARENT

In short, combining these two styles makes a window invisible to all mouse activity (clicks, scroll, etc.) and sends all those events down to the underlying window. This happens even if the layered window is visible and painting content.

## The Problem

After installing the Creator's Update this week on my Windows 10 desktop, I noticed that an app I wrote and use was no longer passing mouse events through to the Edge browser when it happened to be the next window down. It is as if my app window suddenly loses its extended styles *only* when floating over Edge. 

This never happened before and does not happen with any other application – not even any of the other core Windows 10 apps such as Store, Mail, etc.

Thinking this could be a video card driver issue of some kind, I ran the update on my laptop and saw the same results.

## Who Cares?

This sounds like an edge case (</pun>), an irrelevant consequence of some jerk (me) stubbornly clinging to a programming paradigm that no one wants anymore. But transparent, layered windows are still very relevant for some accessibility applications. In this case, I use the above styles to create a fullscreen window that hosts a magnification control provided by Microsoft's Magnification API. This allows the user to view a magnified version of the screen that follows the mouse as it moves around the screen. More importantly, it allows mouse clicks to fall through to whatever application they are viewing. This has and continues to work extremely well. But after the Creator's Update, when the user moves the mouse anywhere over the content frame of the Edge browser, clicks appear to just fall into a void. The user can see a nice magnified web page, but they cannot click on any links, highlight text, scroll, etc.

At this point, someone would just suggest using the magnifier app built into Windows 10 as it sort of bypasses the windowing system altogether and goes straight to the hardware layer. That's true and it does seem to avoid the problem in Edge, but the built-in app is limited in flexibility that can otherwise be achieved through the Magnification API. 

## Demonstration

In this very simplified demo, I've stripped everything down to just a layered transparent window that hovers in the middle of the screen. It was built using Visual Studio 2017. If you run the application, you will see a translucent blue window floating in the center of the screen. 

Experiment clicking on the window and notice how the application underneath behaves as if the floating window didn't really exist. 

This is as expected. 

Now open Microsoft Edge, open your favorite website and try clicking some links. Nothing happens.

This illustrates how Edge is somehow interfering with the styling of the layered window. 

What gives?