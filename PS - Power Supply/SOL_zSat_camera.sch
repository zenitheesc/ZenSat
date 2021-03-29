<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.0.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="1" unitdist="mm" unit="mm" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="sil_26x52">
<packages>
<package name="SOLAR_52X26">
<wire x1="-26" y1="0" x2="-26" y2="26" width="0.1524" layer="21"/>
<wire x1="-26" y1="26" x2="26" y2="26" width="0.1524" layer="21"/>
<wire x1="26" y1="26" x2="26" y2="0" width="0.1524" layer="21"/>
<wire x1="26" y1="0" x2="-26" y2="0" width="0.1524" layer="21"/>
<smd name="TOP" x="0" y="28.5" dx="3" dy="2.5" layer="1"/>
<smd name="BOTTOM" x="0" y="28.5" dx="3" dy="2.5" layer="16"/>
<wire x1="1.5" y1="1.5" x2="1.5" y2="24" width="0.1524" layer="46"/>
<wire x1="1.5" y1="24" x2="0" y2="25.5" width="0.1524" layer="46" curve="90"/>
<wire x1="0" y1="25.5" x2="-1.5" y2="24" width="0.1524" layer="46" curve="90"/>
<wire x1="-1.5" y1="24" x2="-1.5" y2="1.5" width="0.1524" layer="46"/>
<wire x1="-1.5" y1="1.5" x2="0" y2="0" width="0.1524" layer="46" curve="90"/>
<wire x1="0" y1="0" x2="1.5" y2="1.5" width="0.1524" layer="46" curve="90"/>
<wire x1="-1.5" y1="1.5" x2="0" y2="0" width="0.1524" layer="20" curve="90"/>
<wire x1="0" y1="0" x2="1.5" y2="1.5" width="0.1524" layer="20" curve="90"/>
<wire x1="1.5" y1="1.5" x2="1.5" y2="24" width="0.1524" layer="20"/>
<wire x1="1.5" y1="24" x2="0" y2="25.5" width="0.1524" layer="20" curve="90"/>
<wire x1="0" y1="25.5" x2="-1.5" y2="24" width="0.1524" layer="20" curve="90"/>
<wire x1="-1.5" y1="24" x2="-1.5" y2="1.5" width="0.1524" layer="20"/>
</package>
</packages>
<symbols>
<symbol name="SOL_26X52">
<wire x1="-12.7" y1="7.62" x2="-12.7" y2="-7.62" width="0.1524" layer="94"/>
<wire x1="-12.7" y1="-7.62" x2="12.7" y2="-7.62" width="0.1524" layer="94"/>
<wire x1="12.7" y1="-7.62" x2="12.7" y2="7.62" width="0.1524" layer="94"/>
<wire x1="12.7" y1="7.62" x2="-12.7" y2="7.62" width="0.1524" layer="94"/>
<pin name="TOP" x="-17.78" y="0" length="middle"/>
<pin name="BOTTOM" x="17.78" y="0" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SOL_26X52">
<gates>
<gate name="G$1" symbol="SOL_26X52" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOLAR_52X26">
<connects>
<connect gate="G$1" pin="BOTTOM" pad="BOTTOM"/>
<connect gate="G$1" pin="TOP" pad="TOP"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-molex" urn="urn:adsk.eagle:library:165">
<description>&lt;b&gt;Molex Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="53047-02" library_version="2">
<description>&lt;b&gt;1.25mm Pitch PicoBlade™ Wire-to-Board Header, Vertical, with Friction Lock, 2 Circuits&lt;/b&gt;&lt;p&gt;&lt;a href =http://www.molex.com/pdm_docs/sd/530470210_sd.pdf&gt;Datasheet &lt;/a&gt;</description>
<wire x1="-2.025" y1="-1.5" x2="2.025" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="2.025" y1="-1.5" x2="2.025" y2="1.5" width="0.2032" layer="21"/>
<wire x1="2.025" y1="1.5" x2="-2.025" y2="1.5" width="0.2032" layer="21"/>
<wire x1="-2.025" y1="1.5" x2="-2.025" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="-2" y1="-0.25" x2="-1.625" y2="-0.25" width="0.0508" layer="21"/>
<wire x1="-1.625" y1="-0.25" x2="-1.625" y2="-1.25" width="0.0508" layer="21"/>
<wire x1="1.625" y1="-0.25" x2="2" y2="-0.25" width="0.0508" layer="21"/>
<wire x1="1.625" y1="-0.25" x2="1.625" y2="-1.25" width="0.0508" layer="21"/>
<wire x1="-2" y1="0.375" x2="-1.625" y2="0.375" width="0.0508" layer="21"/>
<wire x1="1.625" y1="0.375" x2="2" y2="0.375" width="0.0508" layer="21"/>
<wire x1="-1.625" y1="0.375" x2="-1.625" y2="1.125" width="0.0508" layer="21"/>
<wire x1="-1.625" y1="1.125" x2="1.625" y2="1.125" width="0.0508" layer="21"/>
<wire x1="1.625" y1="1.125" x2="1.625" y2="0.375" width="0.0508" layer="21"/>
<wire x1="1.625" y1="1.125" x2="1.875" y2="1.375" width="0.0508" layer="21"/>
<wire x1="-1.625" y1="1.125" x2="-1.875" y2="1.375" width="0.0508" layer="21"/>
<pad name="1" x="0.625" y="0.45" drill="0.5" diameter="0.6984" shape="long" rot="R90"/>
<pad name="2" x="-0.625" y="0.45" drill="0.5" diameter="0.6984" shape="long" rot="R90"/>
<text x="-1.875" y="1.75" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.375" y="-3.25" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2" y1="-1.5" x2="2" y2="-1.125" layer="21"/>
</package>
<package name="53048-02" library_version="2">
<description>&lt;b&gt;1.25mm Pitch PicoBlade™ Header, Right Angle, 2 Circuits&lt;/b&gt;&lt;p&gt;&lt;a href =http://www.molex.com/pdm_docs/sd/530480210_sd.pdf&gt;Datasheet &lt;/a&gt;</description>
<wire x1="-2.025" y1="-2.25" x2="-1.5" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="1.5" y1="-2.25" x2="2.025" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="2.025" y1="-2.25" x2="2.025" y2="3.125" width="0.2032" layer="21"/>
<wire x1="2.025" y1="3.125" x2="1.875" y2="3.125" width="0.2032" layer="21"/>
<wire x1="1.875" y1="3.125" x2="-1.875" y2="3.125" width="0.2032" layer="21"/>
<wire x1="-1.875" y1="3.125" x2="-2.025" y2="3.125" width="0.2032" layer="21"/>
<wire x1="-2.025" y1="3.125" x2="-2.025" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-2" y1="1.5" x2="-1.5" y2="1.5" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="1.5" x2="-1.25" y2="1.5" width="0.0508" layer="21"/>
<wire x1="-1.25" y1="1.5" x2="-1.25" y2="0.625" width="0.0508" layer="21"/>
<wire x1="-1.25" y1="0.625" x2="1.25" y2="0.625" width="0.0508" layer="21"/>
<wire x1="1.25" y1="1.5" x2="1.5" y2="1.5" width="0.0508" layer="21"/>
<wire x1="1.5" y1="1.5" x2="2" y2="1.5" width="0.0508" layer="21"/>
<wire x1="1.25" y1="1.5" x2="1.25" y2="0.625" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="-1" x2="1.5" y2="-1" width="0.2032" layer="51"/>
<wire x1="-0.875" y1="-1.5" x2="-1" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="0.375" y1="-1.5" x2="0.25" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="0.25" y1="-1.625" x2="-0.25" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="-0.375" y1="-1.5" x2="-0.25" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="1.5" y1="-1.625" x2="1" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="0.875" y1="-1.5" x2="1" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="-1" y1="-1.625" x2="-1.5" y2="-1.625" width="0.2032" layer="51"/>
<wire x1="-2" y1="-1" x2="-1.5" y2="-1" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="-1" x2="-1.5" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="1.5" y1="-1" x2="2" y2="-1" width="0.2032" layer="21"/>
<wire x1="1.5" y1="-1" x2="1.5" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="1.5" x2="-1.5" y2="2.75" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="2.75" x2="1.5" y2="2.75" width="0.0508" layer="21"/>
<wire x1="1.5" y1="2.75" x2="1.5" y2="1.5" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="2.75" x2="-1.875" y2="3.125" width="0.0508" layer="21"/>
<wire x1="1.5" y1="2.75" x2="1.875" y2="3.125" width="0.0508" layer="21"/>
<wire x1="-0.75" y1="1.5" x2="-0.625" y2="2" width="0.2032" layer="21"/>
<wire x1="-0.625" y1="2" x2="-0.5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="0.5" y1="1.5" x2="0.625" y2="2" width="0.2032" layer="21"/>
<wire x1="0.625" y1="2" x2="0.75" y2="1.5" width="0.2032" layer="21"/>
<pad name="1" x="0.625" y="-1.25" drill="0.5" diameter="0.6984" shape="long" rot="R90"/>
<pad name="2" x="-0.625" y="-1.25" drill="0.5" diameter="0.6984" shape="long" rot="R90"/>
<text x="-1.875" y="3.375" size="1.27" layer="25">&gt;NAME</text>
<text x="-2" y="-3.875" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.875" y1="-1.5" x2="-0.375" y2="-1" layer="51"/>
<rectangle x1="0.375" y1="-1.5" x2="0.875" y2="-1" layer="51"/>
<rectangle x1="-0.875" y1="0.625" x2="-0.375" y2="1.5" layer="21"/>
<rectangle x1="0.375" y1="0.625" x2="0.875" y2="1.5" layer="21"/>
</package>
<package name="53261-02" library_version="2">
<description>&lt;b&gt;1.25mm Pitch PicoBlade™ Header, Surface Mount, Right Angle, 2 Circuits&lt;/b&gt;&lt;p&gt;&lt;a href =http://www.molex.com/pdm_docs/sd/532610271_sd.pdf&gt;Datasheet &lt;/a&gt;</description>
<wire x1="-2.025" y1="-1.375" x2="-1.5" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="-1.375" x2="1.5" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="1.5" y1="-1.375" x2="2.025" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="2.025" y1="-1.375" x2="2.025" y2="2.625" width="0.2032" layer="21"/>
<wire x1="2.025" y1="2.625" x2="1.875" y2="2.625" width="0.2032" layer="21"/>
<wire x1="1.875" y1="2.625" x2="-1.875" y2="2.625" width="0.2032" layer="21"/>
<wire x1="-1.875" y1="2.625" x2="-2.025" y2="2.625" width="0.2032" layer="21"/>
<wire x1="-2.025" y1="2.625" x2="-2.025" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="-2" y1="1.625" x2="-1.5" y2="1.625" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="1.625" x2="-1.25" y2="1.625" width="0.0508" layer="21"/>
<wire x1="-1.25" y1="1.625" x2="-1.25" y2="1" width="0.0508" layer="21"/>
<wire x1="-1.25" y1="1" x2="1.25" y2="1" width="0.0508" layer="21"/>
<wire x1="1.25" y1="1.625" x2="1.5" y2="1.625" width="0.0508" layer="21"/>
<wire x1="1.5" y1="1.625" x2="2" y2="1.625" width="0.0508" layer="21"/>
<wire x1="1.25" y1="1.625" x2="1.25" y2="1" width="0.0508" layer="21"/>
<wire x1="-2" y1="-0.75" x2="-1.5" y2="-0.75" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="-0.75" x2="-1.5" y2="-1.375" width="0.0508" layer="21"/>
<wire x1="1.5" y1="-0.75" x2="2" y2="-0.75" width="0.0508" layer="21"/>
<wire x1="1.5" y1="-0.75" x2="1.5" y2="-1.375" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="1.625" x2="-1.5" y2="2.25" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="2.25" x2="1.5" y2="2.25" width="0.0508" layer="21"/>
<wire x1="1.5" y1="2.25" x2="1.5" y2="1.625" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="2.25" x2="-1.875" y2="2.625" width="0.0508" layer="21"/>
<wire x1="1.5" y1="2.25" x2="1.875" y2="2.625" width="0.0508" layer="21"/>
<wire x1="-0.875" y1="-1.25" x2="-0.875" y2="-0.75" width="0.0508" layer="21"/>
<wire x1="-0.875" y1="-0.75" x2="-0.375" y2="-0.75" width="0.0508" layer="21"/>
<wire x1="-0.375" y1="-0.75" x2="-0.375" y2="-1.25" width="0.0508" layer="21"/>
<wire x1="0.375" y1="-1.25" x2="0.375" y2="-0.75" width="0.0508" layer="21"/>
<wire x1="0.375" y1="-0.75" x2="0.875" y2="-0.75" width="0.0508" layer="21"/>
<wire x1="0.875" y1="-0.75" x2="0.875" y2="-1.25" width="0.0508" layer="21"/>
<wire x1="-2.125" y1="2.25" x2="-4" y2="2.25" width="0.2032" layer="51"/>
<wire x1="-4" y1="2.25" x2="-4" y2="-0.75" width="0.2032" layer="51"/>
<wire x1="-4" y1="-0.75" x2="-2.125" y2="-0.75" width="0.2032" layer="51"/>
<wire x1="2.125" y1="-0.75" x2="4" y2="-0.75" width="0.2032" layer="51"/>
<wire x1="4" y1="-0.75" x2="4" y2="2.25" width="0.2032" layer="51"/>
<wire x1="4" y1="2.25" x2="2.125" y2="2.25" width="0.2032" layer="51"/>
<smd name="1" x="0.625" y="-2.5" dx="0.8" dy="2" layer="1"/>
<smd name="2" x="-0.625" y="-2.5" dx="0.8" dy="2" layer="1"/>
<smd name="S1" x="3.125" y="0.625" dx="2.1" dy="3" layer="1"/>
<smd name="S2" x="-3.125" y="0.625" dx="2.1" dy="3" layer="1"/>
<text x="-1.875" y="2.875" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.625" y="-3" size="1.27" layer="27">&gt;VALUE</text>
<text x="2.5" y="-0.25" size="1.9304" layer="51">1</text>
<rectangle x1="-0.875" y1="1" x2="-0.375" y2="1.875" layer="21"/>
<rectangle x1="0.375" y1="1" x2="0.875" y2="1.875" layer="21"/>
</package>
<package name="53398-02" library_version="2">
<description>&lt;b&gt;1.25mm Pitch PicoBlade™ Header, Surface Mount, Vertical, 2 Circuits&lt;/b&gt;&lt;p&gt;&lt;a href =http://www.molex.com/pdm_docs/sd/533980271_sd.pdf&gt;Datasheet &lt;/a&gt;</description>
<wire x1="-2.025" y1="-1.375" x2="-1.25" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="-1.25" y1="-1.375" x2="1.25" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="1.25" y1="-1.375" x2="2.025" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="2.025" y1="-1.375" x2="2.025" y2="2.125" width="0.2032" layer="21"/>
<wire x1="2.025" y1="2.125" x2="1.875" y2="2.125" width="0.2032" layer="21"/>
<wire x1="1.875" y1="2.125" x2="-1.875" y2="2.125" width="0.2032" layer="21"/>
<wire x1="-1.875" y1="2.125" x2="-2.025" y2="2.125" width="0.2032" layer="21"/>
<wire x1="-2.025" y1="2.125" x2="-2.025" y2="-1.375" width="0.2032" layer="21"/>
<wire x1="-2" y1="1" x2="-1.5" y2="1" width="0.0508" layer="21"/>
<wire x1="1.5" y1="1" x2="2" y2="1" width="0.0508" layer="21"/>
<wire x1="-2" y1="-0.25" x2="-1.5" y2="-0.25" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="-0.25" x2="-1.5" y2="-1" width="0.0508" layer="21"/>
<wire x1="1.5" y1="-0.25" x2="2" y2="-0.25" width="0.0508" layer="21"/>
<wire x1="1.5" y1="-0.25" x2="1.5" y2="-1" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="1" x2="-1.5" y2="1.75" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="1.75" x2="1.5" y2="1.75" width="0.0508" layer="21"/>
<wire x1="1.5" y1="1.75" x2="1.5" y2="1" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="1.75" x2="-1.875" y2="2.125" width="0.0508" layer="21"/>
<wire x1="1.5" y1="1.75" x2="1.875" y2="2.125" width="0.0508" layer="21"/>
<wire x1="-2.125" y1="2.125" x2="-4" y2="2.125" width="0.2032" layer="51"/>
<wire x1="-4" y1="2.125" x2="-4" y2="-0.75" width="0.2032" layer="51"/>
<wire x1="-4" y1="-0.75" x2="-2.125" y2="-0.75" width="0.2032" layer="51"/>
<wire x1="2.125" y1="-0.75" x2="4" y2="-0.75" width="0.2032" layer="51"/>
<wire x1="4" y1="-0.75" x2="4" y2="2.125" width="0.2032" layer="51"/>
<wire x1="4" y1="2.125" x2="2.125" y2="2.125" width="0.2032" layer="51"/>
<wire x1="-2" y1="-1" x2="-1.5" y2="-1" width="0.0508" layer="21"/>
<wire x1="-1.5" y1="-1" x2="-1.25" y2="-1" width="0.0508" layer="21"/>
<wire x1="-1.25" y1="-1" x2="-1.25" y2="-1.375" width="0.0508" layer="21"/>
<wire x1="1.5" y1="-1" x2="2" y2="-1" width="0.0508" layer="21"/>
<wire x1="1.25" y1="-1" x2="1.5" y2="-1" width="0.0508" layer="21"/>
<wire x1="1.25" y1="-1" x2="1.25" y2="-1.375" width="0.0508" layer="21"/>
<smd name="1" x="0.625" y="-2.5" dx="0.8" dy="1.8" layer="1"/>
<smd name="2" x="-0.625" y="-2.5" dx="0.8" dy="1.8" layer="1"/>
<smd name="S1" x="3.125" y="0.625" dx="2.1" dy="3" layer="1"/>
<smd name="S2" x="-3.125" y="0.625" dx="2.1" dy="3" layer="1"/>
<text x="-3" y="2.375" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.5" y="-3.5" size="1.27" layer="27">&gt;VALUE</text>
<text x="2.5" y="-0.25" size="1.9304" layer="51">1</text>
<rectangle x1="-0.875" y1="0.375" x2="-0.375" y2="1" layer="21"/>
<rectangle x1="0.375" y1="0.375" x2="0.875" y2="1" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="MV" library_version="2">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M" library_version="2">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="53?-02" prefix="X" library_version="2">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
wire to board 1.25 mm (.049 inch) pitch header</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="047" package="53047-02">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="53047-0210" constant="no"/>
<attribute name="OC_FARNELL" value="9733051" constant="no"/>
<attribute name="OC_NEWARK" value="57H4701" constant="no"/>
</technology>
</technologies>
</device>
<device name="048" package="53048-02">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="53048-0210" constant="no"/>
<attribute name="OC_FARNELL" value="1012259" constant="no"/>
<attribute name="OC_NEWARK" value="57H4718" constant="no"/>
</technology>
</technologies>
</device>
<device name="261" package="53261-02">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="1125373" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="398" package="53398-02">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="sil_26x52" deviceset="SOL_26X52" device=""/>
<part name="U$2" library="sil_26x52" deviceset="SOL_26X52" device=""/>
<part name="U$3" library="sil_26x52" deviceset="SOL_26X52" device=""/>
<part name="U$4" library="sil_26x52" deviceset="SOL_26X52" device=""/>
<part name="U$5" library="sil_26x52" deviceset="SOL_26X52" device=""/>
<part name="U$6" library="sil_26x52" deviceset="SOL_26X52" device=""/>
<part name="X1" library="con-molex" library_urn="urn:adsk.eagle:library:165" deviceset="53?-02" device="398"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="-36.83" y="54.61"/>
<instance part="U$2" gate="G$1" x="8.89" y="54.61"/>
<instance part="U$3" gate="G$1" x="53.34" y="54.61"/>
<instance part="U$4" gate="G$1" x="97.79" y="54.61"/>
<instance part="U$5" gate="G$1" x="139.7" y="54.61"/>
<instance part="U$6" gate="G$1" x="180.34" y="54.61"/>
<instance part="X1" gate="-1" x="5.08" y="20.32"/>
<instance part="X1" gate="-2" x="5.08" y="17.78"/>
</instances>
<busses>
</busses>
<nets>
<net name="SOL-" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="TOP"/>
<wire x1="-54.61" y1="54.61" x2="-64.77" y2="54.61" width="0.1524" layer="91"/>
<label x="-64" y="55" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="X1" gate="-2" pin="S"/>
<wire x1="2.54" y1="17.78" x2="-9" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-9" y1="17.78" x2="-9" y2="17" width="0.1524" layer="91"/>
<label x="-7" y="18" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="BOTTOM"/>
<pinref part="U$2" gate="G$1" pin="TOP"/>
<wire x1="-19.05" y1="54.61" x2="-8.89" y2="54.61" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="BOTTOM"/>
<pinref part="U$3" gate="G$1" pin="TOP"/>
<wire x1="26.67" y1="54.61" x2="35.56" y2="54.61" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="BOTTOM"/>
<pinref part="U$4" gate="G$1" pin="TOP"/>
<wire x1="71.12" y1="54.61" x2="80.01" y2="54.61" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="BOTTOM"/>
<pinref part="U$5" gate="G$1" pin="TOP"/>
<wire x1="115.57" y1="54.61" x2="121.92" y2="54.61" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="BOTTOM"/>
<pinref part="U$6" gate="G$1" pin="TOP"/>
<wire x1="157.48" y1="54.61" x2="162.56" y2="54.61" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SOL+" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="BOTTOM"/>
<wire x1="198.12" y1="54.61" x2="205" y2="54.61" width="0.1524" layer="91"/>
<wire x1="205" y1="54.61" x2="205" y2="55" width="0.1524" layer="91"/>
<label x="204" y="55" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="X1" gate="-1" pin="S"/>
<wire x1="2.54" y1="20.32" x2="-9" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-9" y1="20.32" x2="-9" y2="21" width="0.1524" layer="91"/>
<label x="-7" y="21" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
</compatibility>
</eagle>
