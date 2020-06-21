const getElementByID = (id) => {
    return document.getElementById(id);
};

const openSlideMenu = () => {
    let hamburgerButton = getElementByID("hamburger-button");
    let slideMenu = getElementByID("slide-menu");

    console.log(slideMenu.style.display);
    if (slideMenu.style.display !== "none") {
        slideMenu.style.display = "none";
        hamburgerButton.style.transform = "rotateZ(90deg)";
    } else {
        slideMenu.style.display = "revert";

        hamburgerButton.style.transform = "rotateZ(45deg)";

    }
};

const setEventListener = (id, type, action) => {
    getElementByID(id).addEventListener(type, action);
};

setEventListener("hamburger-button", "click", openSlideMenu);