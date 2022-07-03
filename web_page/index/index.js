// This example displays a marker at the center of Australia.
// When the user clicks the marker, an info window opens.
import { ajax } from '../assets/ajax.js';

function initMap(member_selected)
{
    const pos = get_init_data(member_selected["name"]).coords;
    const map = new google.maps.Map(document.getElementById("map"), 
    {
        zoom: 18,
        center: pos,
    });
    get_sql_data_and_set_marker(member_selected["name"],map);
}
function initMap_all(loc,member_list)
{
    var icons = ["./image/red_icon.png","./image/blue_icon.png","./image/orange_icon.png","./image/purple_icon.png"];
    const pos = loc.coords;
    const map = new google.maps.Map(document.getElementById("map"), 
    {
        zoom: 18,
        center: pos,
    });
    let count = -1;
    member_list.forEach(element => 
    {
        count++;
        get_sql_data_and_set_marker(element["name"],map,icons[count]);
    });
}
function get_init_data(call_name)
{
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "./index/get_newest_position.php", false);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send(`call_name=${call_name}`);
    if (xhttp.status === 200) {
        var result =  JSON.parse(xhttp.responseText);
    }
    return {coords:{lat:parseFloat(result[0]["lat"]),lng:parseFloat(result[0]["lng"])}};
}
function get_sql_data_and_set_marker(call_name,map,icon) 
{
    var result = '';
    return ajax(
    {
        type: "POST",
        url: "./index/get_newest_position.php",
        data: 
        {
            "call_name": call_name
        },
        async:false,
        callback: function(xhr) {
            if (xhr.readyState == 4 && xhr.status == 200) 
            {
                result = JSON.parse(xhr.response);
                console.log(result);
                result.forEach(element => 
                {
                    let infowindow = new google.maps.InfoWindow({
                        content: ""+ element["time"]
                    })
                    let props = {
                        coords:{lat:parseFloat(element["lat"]),lng:parseFloat(element["lng"])},
                        title:call_name,
                        infowindow_content:infowindow,
                        icon:icon
                    };
                    addMarker(map,props);
                });
            }
        }
    });
}

function addMarker(map, props)
{
    var marker = new google.maps.Marker({
        position:props.coords,
        map:map,
        icon: props.icon,
        title:props.call_name,
    });
    marker.addListener("click",()=>
    {
        props.infowindow_content.open(
            {
                anchor:marker,
                map:map,
                shouldFocus: false
            }
        );
    });
}

function get_member_list()
{
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "./index/get_member_list.php", false);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("call_name='123'");
    if (xhttp.status === 200) {
        var result =  JSON.parse(xhttp.responseText);
    }
    //return {coords:{lat:parseFloat(result[0]["lat"]),lng:parseFloat(result[0]["lng"])}};
    return result;
}

$(document).ready(function()
{
    var member_list = get_member_list();
    console.log(member_list);
    $("#all").click(function(){
        $("#member_list_button").text("ALL");
    });
    member_list.forEach(element => 
        {
            $("#member_list").append(`<li><button class='dropdown-item' id=${element["client_id"]}>${element["name"]}</button></li>`)
            $(`#${element["client_id"]}`).click(function(){
                $("#member_list_button").text(`${element["name"]}`);
                initMap(element);
            });
        }
    );
    $("#all").click(function(){
        initMap_all({coords:{lat:parseFloat(22.9889442),lng:parseFloat(120.2166515)}}, member_list);
    });
    $("#en_map").click(function()
    {
        var member_selected = '';
        member_list.forEach(element => {
            if(element["name"] == $("#member_list_button").html())
            {
                member_selected = element;
            }
        });
        if($("#member_list_button").html() == "ALL")
        {
            initMap_all({coords:{lat:parseFloat(22.9889442),lng:parseFloat(120.2166515)}}, member_list);
        }
        else
        {
            //initMap(member_selected);
        }
        console.log(member_selected);
        
    });
});
